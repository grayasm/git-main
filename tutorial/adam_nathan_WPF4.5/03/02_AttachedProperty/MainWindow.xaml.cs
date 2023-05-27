using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace AttachedProperty
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            // MainWindow.xaml.cs(25,13,25,32): error CS0103: The name 'InitializeComponent' does not exist in the current context
            // InitializeComponent();

            // The StackPanel declaration in MainWindow.xaml is equivalent to the following C#

            StackPanel panel = new StackPanel();
            TextElement.SetFontSize(panel, 30);
            TextElement.SetFontStyle(panel, FontStyles.Italic);
            panel.Orientation = Orientation.Horizontal;
            panel.HorizontalAlignment = HorizontalAlignment.Center;
            Button helpButton = new Button();
            helpButton.MinWidth = 75;
            helpButton.Margin = new Thickness(10);
            helpButton.Content = "Help";
            Button okButton = new Button();
            okButton.MinWidth = 75;
            okButton.Margin = new Thickness(10);
            okButton.Content = "OK";
            panel.Children.Add(helpButton);
            panel.Children.Add(okButton);
        }
    }
}
