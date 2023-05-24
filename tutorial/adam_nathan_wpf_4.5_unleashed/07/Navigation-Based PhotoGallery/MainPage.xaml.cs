using System;
using System.ComponentModel;
using System.IO;
using System.IO.IsolatedStorage;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Threading;

namespace PhotoGallery
{
    public partial class MainPage : Page
    {
        ScaleTransform st = new ScaleTransform(3, 3);
        object dummyNode = null;
        Photos photos = new Photos();

        #region Window Management

        public MainPage()
        {
            InitializeComponent();
            photos.ItemsUpdated += delegate { this.Dispatcher.Invoke(DispatcherPriority.Normal, new ThreadStart(Refresh)); };
            Application.Current.Properties["favoritesItem"] = favoritesItem;
        }

        protected override void OnInitialized(EventArgs e)
        {
            base.OnInitialized(e);

            // Retrieve the list of favorites
            IsolatedStorageFile f = IsolatedStorageFile.GetUserStoreForAssembly();
            using (IsolatedStorageFileStream stream = new IsolatedStorageFileStream("myFile", FileMode.OpenOrCreate, f))
            using (StreamReader reader = new StreamReader(stream))
            {
                string line = reader.ReadLine();
                while (line != null)
                {
                    AddFavorite(line);
                    line = reader.ReadLine();
                }
            }

            // At least have the user's Pictures folder as a favorite if nothing else
            if (!favoritesItem.HasItems)
            {
                AddFavorite(Environment.GetFolderPath(Environment.SpecialFolder.MyPictures));
            }

            (treeView.Items[0] as TreeViewItem).IsSelected = true;
        }

        #endregion Window Management

        #region TreeView Management

        void folders_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            Refresh();
        }

        void Page_Loaded(object sender, RoutedEventArgs e)
        {
            foreach (string s in Directory.GetLogicalDrives())
            {
                TreeViewItem item = new TreeViewItem();
                item.Header = s;
                item.Tag = s;
                item.Items.Add(dummyNode);
                item.Expanded += new RoutedEventHandler(folder_Expanded);
                foldersItem.Items.Add(item);
            }
        }

        void folder_Expanded(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = (TreeViewItem)sender;
            if (item.Items.Count == 1 && item.Items[0] == dummyNode)
            {
                item.Items.Clear();
                try
                {
                    foreach (string s in Directory.GetDirectories(item.Tag.ToString()))
                    {
                        TreeViewItem subitem = new TreeViewItem();
                        subitem.Header = s.Substring(s.LastIndexOf("\\") + 1);
                        subitem.Tag = s;
                        subitem.Items.Add(dummyNode);
                        subitem.Expanded += new RoutedEventHandler(folder_Expanded);
                        item.Items.Add(subitem);
                    }
                }
                catch (UnauthorizedAccessException) { }
            }
        }

        private void AddFavorite(string folder)
        {
            TreeViewItem item = new TreeViewItem();
            item.Header = folder;
            item.Tag = folder;
            favoritesItem.Items.Add(item);
        }

        private void RemoveFavorite(string folder)
        {
            for (int i = 0; i < favoritesItem.Items.Count; i++)
            {
                if ((favoritesItem.Items[i] as TreeViewItem).Header as string == folder)
                {
                    favoritesItem.Items.RemoveAt(i);
                    break;
                }
            }
        }

        #endregion TreeView Management

        private void ShowPhoto(bool showFixBar)
        {
            string filename = (pictureBox.SelectedItem as ListBoxItem).Tag as string;

            // Navigate to a page instance
            PhotoPage nextPage = new PhotoPage(filename, showFixBar);
            this.NavigationService.Navigate(nextPage);
        }

        void AddPhotosInFolder(string folder)
        {
            try
            {
                foreach (string s in Directory.GetFiles(folder, "*.jpg"))
                {
                    Photo photo = new Photo(s);
                    photos.Add(photo);

                    // Construct the ListBoxItem with an Image as content:
                    ListBoxItem item = new ListBoxItem();
                    item.Padding = new Thickness(3, 8, 3, 8);
                    item.MouseDoubleClick += delegate { ShowPhoto(false); };
                    TransformGroup tg = new TransformGroup();
                    tg.Children.Add(st);
                    tg.Children.Add(new RotateTransform());
                    item.LayoutTransform = tg;
                    item.Tag = s;

                    Image image = new Image();
                    image.Height = 35;

                    // If the image contains a thumbnail, use that instead of the entire image:
                    Uri uri = new Uri(s);
                    BitmapDecoder bd = BitmapDecoder.Create(uri, BitmapCreateOptions.DelayCreation, BitmapCacheOption.Default);
                    if (bd.Frames[0].Thumbnail != null)
                        image.Source = bd.Frames[0].Thumbnail;
                    else
                        image.Source = new BitmapImage(uri);

                    // Construct a ToolTip for the item:
                    Image toolImage = new Image();
                    toolImage.Source = bd.Frames[0].Thumbnail;

                    TextBlock textBlock1 = new TextBlock();
                    textBlock1.Text = System.IO.Path.GetFileName(s);
                    TextBlock textBlock2 = new TextBlock();
                    textBlock2.Text = photo.DateTime.ToString();

                    StackPanel sp = new StackPanel();
                    sp.Children.Add(toolImage);
                    sp.Children.Add(textBlock1);
                    sp.Children.Add(textBlock2);

                    item.ToolTip = sp;
                    item.Content = image;

                    pictureBox.Items.Add(item);
                }
            }
            catch (UnauthorizedAccessException) { }
            catch (IOException) { }
        }

        private void Refresh()
        {
            try
            {
                this.Cursor = Cursors.Wait;

                pictureBox.Items.Clear();
                photos.Clear();

                if (treeView.SelectedItem == favoritesItem)
                {
                    foreach (TreeViewItem item in favoritesItem.Items)
                    {
                        AddPhotosInFolder(item.Tag as string);
                    }
                    favoritesMenu.IsEnabled = false;
                }
                else if (treeView.SelectedItem != foldersItem)
                {
                    string folder = (treeView.SelectedItem as TreeViewItem).Tag as string;
                    AddPhotosInFolder(folder);

                    // Update the favorites menu text depending on whether the folder is already a favorite
                    favoritesMenu.IsEnabled = true;
                    foreach (TreeViewItem item in favoritesItem.Items)
                    {
                        if (item.Header as string == folder)
                        {
                            favoritesMenu.Header = "Remove Current Folder from Fa_vorites";
                            return;
                        }
                    }
                    favoritesMenu.Header = "Add Current Folder to Fa_vorites";
                }
            }
            finally
            {
                this.Cursor = Cursors.Arrow;
            }
        }

        void pictureBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (e.AddedItems.Count == 0)
            {
                deleteMenu.IsEnabled = false;
                renameMenu.IsEnabled = false;
                fixMenu.IsEnabled = false;
                printMenu.IsEnabled = false;
                editMenu.IsEnabled = false;
                previousButton.IsEnabled = false; previousButton.Opacity = 0.5;
                nextButton.IsEnabled = false; nextButton.Opacity = 0.5;
                counterclockwiseButton.IsEnabled = false; counterclockwiseButton.Opacity = 0.5;
                clockwiseButton.IsEnabled = false; clockwiseButton.Opacity = 0.5;
                deleteButton.IsEnabled = false; deleteButton.Opacity = 0.5;

            }
            else
            {
                deleteMenu.IsEnabled = true;
                renameMenu.IsEnabled = true;
                fixMenu.IsEnabled = true;
                printMenu.IsEnabled = true;
                editMenu.IsEnabled = true;
                previousButton.IsEnabled = true; previousButton.Opacity = 1;
                nextButton.IsEnabled = true; nextButton.Opacity = 1;
                counterclockwiseButton.IsEnabled = true; counterclockwiseButton.Opacity = 1;
                clockwiseButton.IsEnabled = true; clockwiseButton.Opacity = 1;
                deleteButton.IsEnabled = true; deleteButton.Opacity = 1;
            }
        }

        #region Menu Handlers

        void favoritesMenu_Click(object sender, RoutedEventArgs e)
        {
            string folder = (treeView.SelectedItem as TreeViewItem).Tag as string;
            if (favoritesMenu.Header as string == "Add Current Folder to Fa_vorites")
            {
                AddFavorite(folder);
                favoritesMenu.Header = "Remove Current Folder from Fa_vorites";
            }
            else
            {
                RemoveFavorite(folder);
                favoritesMenu.Header = "Add Current Folder to Fa_vorites";
            }
        }

        void deleteMenu_Click(object sender, RoutedEventArgs e)
        {
            DeleteCurrentPhoto();
        }

        void renameMenu_Click(object sender, RoutedEventArgs e)
        {
            string filename = (pictureBox.SelectedItem as ListBoxItem).Tag as string;
            RenameDialog dialog = new RenameDialog(Path.GetFileNameWithoutExtension(filename));
            if (dialog.ShowDialog() == true) // Result could be true, false, or null
            {
                // Attempt to rename the file
                try
                {
                    File.Move(filename, Path.Combine(Path.GetDirectoryName(filename), dialog.NewFilename) + Path.GetExtension(filename));
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Cannot Rename File", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        void refreshMenu_Click(object sender, RoutedEventArgs e)
        {
            Refresh();
        }

        void exitMenu_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        void fixMenu_Click(object sender, RoutedEventArgs e)
        {
            ShowPhoto(true);
        }

        void printMenu_Click(object sender, RoutedEventArgs e)
        {
            string filename = (pictureBox.SelectedItem as ListBoxItem).Tag as string;
            Image image = new Image();
            image.Source = new BitmapImage(new Uri(filename, UriKind.RelativeOrAbsolute));

            PrintDialog pd = new PrintDialog();
            if (pd.ShowDialog() == true) // Result could be true, false, or null
                pd.PrintVisual(image, Path.GetFileName(filename) + " from Photo Gallery");
        }

        void editMenu_Click(object sender, RoutedEventArgs e)
        {
            string filename = (pictureBox.SelectedItem as ListBoxItem).Tag as string;
            System.Diagnostics.Process.Start("mspaint.exe", filename);
        }

        #endregion Menu Handlers

        private void DeleteCurrentPhoto()
        {
            string filename = (pictureBox.SelectedItem as ListBoxItem).Tag as string;
            if (MessageBox.Show("Are you sure you want to delete '" + filename + "'?", "Delete Picture", MessageBoxButton.YesNo, MessageBoxImage.Question)
                == MessageBoxResult.Yes)
            {
                try
                {
                    File.Delete(filename);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Cannot Rename File", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        #region Bottom Button Handlers

        void defaultSizeButton_Click(object sender, RoutedEventArgs e)
        {
            zoomSlider.Value = 3;
        }

        void zoomSlider_ValueChanged(object sender, RoutedEventArgs e)
        {
            st.ScaleX = zoomSlider.Value;
            st.ScaleY = zoomSlider.Value;
        }

        void zoomPopup_MouseLeave(object sender, RoutedEventArgs e)
        {
            zoomPopup.IsOpen = false;
        }

        void zoomButton_Click(object sender, RoutedEventArgs e)
        {
            zoomPopup.IsOpen = true;
        }

        void slideshowButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("NYI");
        }

        void clockwiseButton_Click(object sender, RoutedEventArgs e)
        {
            if (pictureBox.SelectedItem != null)
            {
                RotateTransform rt = ((pictureBox.SelectedItem as ListBoxItem).LayoutTransform as TransformGroup).Children[1] as RotateTransform;
                rt.Angle += 90;
            }
        }

        void counterclockwiseButton_Click(object sender, RoutedEventArgs e)
        {
            if (pictureBox.SelectedItem != null)
            {
                RotateTransform rt = ((pictureBox.SelectedItem as ListBoxItem).LayoutTransform as TransformGroup).Children[1] as RotateTransform;
                rt.Angle -= 90;
            }
        }

        void previousButton_Click(object sender, RoutedEventArgs e)
        {
            int index = pictureBox.SelectedIndex - 1;
            if (index < 0) index = pictureBox.Items.Count - 1;
            (pictureBox.Items[index] as ListBoxItem).IsSelected = true;
            pictureBox.ScrollIntoView(pictureBox.SelectedItem);
        }

        void nextButton_Click(object sender, RoutedEventArgs e)
        {
            int index = pictureBox.SelectedIndex + 1;
            if (index == pictureBox.Items.Count) index = 0;
            (pictureBox.Items[index] as ListBoxItem).IsSelected = true;
            pictureBox.ScrollIntoView(pictureBox.SelectedItem);
        }

        void deleteButton_Click(object sender, RoutedEventArgs e)
        {
            DeleteCurrentPhoto();
        }

        #endregion Buttom Button Handlers
    }
}