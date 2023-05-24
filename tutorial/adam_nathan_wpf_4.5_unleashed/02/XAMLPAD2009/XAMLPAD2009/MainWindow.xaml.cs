using System;
using System.Windows;
using System.Windows.Controls;

namespace XAMLPAD2009
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            textBox.Text =
@"<Page xmlns=""http://schemas.microsoft.com/winfx/2006/xaml/presentation""
      xmlns:x=""http://schemas.microsoft.com/winfx/2006/xaml"">
  <Button>Hello, XAMLPAD2009!</Button>
</Page>";
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                frame.Content = Utils.ConvertXmlStringToMorphedObjectGraph(textBox.Text);
            }
            catch (Exception ex)
            {
                frame.Content = ex.ToString();
            }
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                textBox.Text = Utils.RewriteXaml(textBox.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Error Scrubbing XAML");
            }
        }
    }
}
