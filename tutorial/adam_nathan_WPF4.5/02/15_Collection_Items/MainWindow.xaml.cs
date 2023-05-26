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

namespace CollectionItems
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            // Dictionaries exmaple
            System.Windows.ResourceDictionary d = new System.Windows.ResourceDictionary();
            System.Windows.Media.Color color1 = new System.Windows.Media.Color();
            System.Windows.Media.Color color2 = new System.Windows.Media.Color();
            color1.A = 255;
            color1.R=255;
            color1.G=255;
            color1.B=255;
            color2.A = 0;
            color2.R=0;
            color2.G=0;
            color2.B=0;
            d.Add("1", color1);
            d.Add("2", color2);
        }
    }
}
