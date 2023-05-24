using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.IO;

namespace PhotoGallery
{
    public partial class PhotoPage : System.Windows.Controls.Page
    {
        string filename;

        public PhotoPage(string filename, bool showFixBar)
        {
            InitializeComponent();
            this.filename = filename;
            if (showFixBar)
                fixBar.Visibility = Visibility.Visible;

            image.Source = new BitmapImage(new Uri(filename));
        }

        #region Menu Handlers

        void renameMenu_Click(object sender, RoutedEventArgs e)
        {
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

        void exitMenu_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        void fixMenu_Click(object sender, RoutedEventArgs e)
        {
            fixBar.Visibility = Visibility.Visible;
        }

        void printMenu_Click(object sender, RoutedEventArgs e)
        {
            Image image = new Image();
            image.Source = new BitmapImage(new Uri(filename, UriKind.RelativeOrAbsolute));

            PrintDialog pd = new PrintDialog();
            if (pd.ShowDialog() == true) // Result could be true, false, or null
                pd.PrintVisual(image, Path.GetFileName(filename) + " from Photo Gallery");
        }

        void editMenu_Click(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start("mspaint.exe", filename);
        }

        #endregion Menu Handlers

        #region Bottom Button Handlers

        void slideshowButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("NYI");
        }

        void previousButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("NYI");
        }

        void nextButton_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("NYI");
        }

        #endregion Buttom Button Handlers

        #region Fix Bar Handlers

        void fix_RotateClockwise_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.AddBackEntry(new RotateState(image, (image.LayoutTransform as RotateTransform).Angle));
            (image.LayoutTransform as RotateTransform).Angle += 90;
        }

        void fix_RotateCounterclockwise_Click(object sender, RoutedEventArgs e)
        {
            this.NavigationService.AddBackEntry(new RotateState(image, (image.LayoutTransform as RotateTransform).Angle));
            (image.LayoutTransform as RotateTransform).Angle -= 90;
        }

        void fix_Save_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("NYI");
        }

        #endregion Fix Bar Handlers
    }
}