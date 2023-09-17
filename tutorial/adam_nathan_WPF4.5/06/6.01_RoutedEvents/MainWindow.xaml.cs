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

namespace RoutedEvents
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        void MainWindow_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            // Display information about this event
            this.Title = "Source = " + e.Source.GetType().Name + ", OriginalSource = " +
            e.OriginalSource.GetType().Name + " @ " + e.Timestamp;
            // In this example, all possible sources derive from Control
            Control source = e.Source as Control;
            // Toggle the border on the source control
            if (source.BorderThickness != new Thickness(5))
            {
                source.BorderThickness = new Thickness(5);
                source.BorderBrush = Brushes.Black;
            }
            else
                source.BorderThickness = new Thickness(0);
        }

    }
}
