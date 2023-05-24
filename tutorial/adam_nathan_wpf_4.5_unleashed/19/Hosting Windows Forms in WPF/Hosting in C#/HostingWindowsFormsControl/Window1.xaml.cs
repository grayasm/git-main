using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows.Shapes;

namespace HostingWindowsFormsControl
{
    public partial class Window1 : Window
    {
        public Window1()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            // Create the host and the PropertyGrid control
            System.Windows.Forms.Integration.WindowsFormsHost host =
                new System.Windows.Forms.Integration.WindowsFormsHost();
            System.Windows.Forms.PropertyGrid propertyGrid =
                new System.Windows.Forms.PropertyGrid();

            // Add the PropertyGrid to the host, and the host to the WPF Grid
            host.Child = propertyGrid;
            grid.Children.Add(host);
            
            // Set a PropertyGrid-specific property
            propertyGrid.SelectedObject = this;
        }
    }
}