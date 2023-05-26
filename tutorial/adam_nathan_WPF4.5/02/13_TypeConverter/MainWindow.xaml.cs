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

namespace TypeConverter
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();


            // Create a Brush using a TypeConverter
            System.ComponentModel.TypeConverter tc = System.ComponentModel.TypeDescriptor.GetConverter(typeof(Brush));
            Brush br = (Brush)tc.ConvertFromInvariantString("White");

            // Grab the OK button, knowing only its name
            Button b = (Button)this.FindName("okButton");
            b.Background = br;

            // Crate a Brush differently
            System.Windows.Shapes.Rectangle r = new System.Windows.Shapes.Rectangle();
            r.Width = 40;
            r.Height = 40;
            r.Fill = System.Windows.Media.Brushes.Black;
            b.Content = r;


            // Display the Window
            this.Show();

            // Show the Button's Content
            MessageBox.Show(okButton.Content.ToString());
        }
    }
}
