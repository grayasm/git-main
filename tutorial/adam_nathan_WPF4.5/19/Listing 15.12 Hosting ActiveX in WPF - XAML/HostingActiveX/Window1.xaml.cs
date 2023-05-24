using System;
using System.Windows;
using System.Windows.Forms.Integration;

namespace HostingActiveX
{
    public partial class Window1 : Window
    {
        public Window1()
        {
            InitializeComponent();
        }

        void connectButton_Click(object sender, RoutedEventArgs e)
        {
            termServ.Server = serverBox.Text;
            termServ.Connect();
        }
    }
}