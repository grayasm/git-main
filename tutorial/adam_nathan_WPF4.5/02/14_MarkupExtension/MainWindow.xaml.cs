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

namespace MarkupExtension
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            // Chapter 2 XAML Demystified
            // the following Button is identical with the "markupButton" from XAML

            System.Windows.Controls.Button b = new System.Windows.Controls.Button();
            b.Name = "markupButton2";
            b.Background = null;
            b.Height = System.Windows.SystemParameters.IconHeight;
            System.Windows.Data.Binding binding = new System.Windows.Data.Binding();
            binding.Path = new System.Windows.PropertyPath("Height");
            binding.RelativeSource = System.Windows.Data.RelativeSource.Self;
            b.SetBinding(System.Windows.Controls.Button.ContentProperty, binding);
        }
    }
}
