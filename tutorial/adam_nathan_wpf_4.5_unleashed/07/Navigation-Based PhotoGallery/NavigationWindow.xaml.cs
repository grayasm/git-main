using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Navigation;
using System.IO;
using System.IO.IsolatedStorage;

namespace PhotoGallery
{
    public partial class Container : NavigationWindow
    {
        public Container()
        {
            InitializeComponent();
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosing(e);

            if (MessageBox.Show("Are you sure you want to close Photo Gallery?", "Annoying Prompt", MessageBoxButton.YesNo, MessageBoxImage.Question)
                == MessageBoxResult.No)
                e.Cancel = true;
        }

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);

            // Persist the list of favorites
            IsolatedStorageFile f = IsolatedStorageFile.GetUserStoreForAssembly();
            using (IsolatedStorageFileStream stream = new IsolatedStorageFileStream("myFile", FileMode.Create, f))
            using (StreamWriter writer = new StreamWriter(stream))
            {
                foreach (TreeViewItem item in (Application.Current.Properties["favoritesItem"] as TreeViewItem).Items)
                {
                    writer.WriteLine(item.Tag as string);
                }
            }
        }
    }
}