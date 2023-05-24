using System;
using System.IO;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace PhotoGallery
{
    public class Photos : ObservableCollection<Photo>
    {
        Dictionary<string, FileSystemWatcher> watchers = new Dictionary<string, FileSystemWatcher>();

        public event EventHandler ItemsUpdated;

        protected override void ClearItems()
        {
            base.ClearItems();
            watchers.Clear();
        }

        protected override void InsertItem(int index, Photo item)
        {
            base.InsertItem(index, item);
            if (!watchers.ContainsKey(item.Path))
            {
                FileSystemWatcher watcher = new FileSystemWatcher(item.Path, "*.jpg");
                watcher.EnableRaisingEvents = true;
                watcher.Created += new System.IO.FileSystemEventHandler(OnPhotoCreated);
                watcher.Deleted += new System.IO.FileSystemEventHandler(OnPhotoDeleted);
                watcher.Renamed += new System.IO.RenamedEventHandler(OnPhotoRenamed);
                watchers.Add(item.Path, watcher);
            }
        }

        void OnPhotoRenamed(object sender, System.IO.RenamedEventArgs e)
        {
            int index = -1;
            for (int i = 0; i < Items.Count; i++)
            {
                if (Items[i].FullPath == e.OldFullPath)
                {
                    index = i;
                    break;
                }
            }
            if (index >= 0)
                Items[index] = new Photo(e.FullPath);

            if (ItemsUpdated != null)
                ItemsUpdated(this, new EventArgs());
        }

        void OnPhotoDeleted(object sender, System.IO.FileSystemEventArgs e)
        {
            int index = -1;
            for (int i = 0; i < Items.Count; i++)
            {
                if (Items[i].FullPath == e.FullPath)
                {
                    index = i;
                    break;
                }
            }
            if (index >= 0)
                Items.RemoveAt(index);

            if (ItemsUpdated != null)
                ItemsUpdated(this, new EventArgs());
        }

        void OnPhotoCreated(object sender, System.IO.FileSystemEventArgs e)
        {
            Items.Add(new Photo(e.FullPath));

            if (ItemsUpdated != null)
                ItemsUpdated(this, new EventArgs());
        }
    }
}
