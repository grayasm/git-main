using System;
using System.Windows;
using System.Windows.Forms.Integration;

namespace HostingActiveX
{
    public partial class Window1 : Window
    {
        AxMSTSCLib.AxMsTscAxNotSafeForScripting termServ;

        public Window1()
        {
            InitializeComponent();

            // Create the host and the ActiveX control
            WindowsFormsHost host = new WindowsFormsHost();
            termServ = new AxMSTSCLib.AxMsTscAxNotSafeForScripting();

            // Add the ActiveX control to the host, and the host to the WPF panel
            host.Child = termServ;
            panel.Children.Add(host);
        }

        void connectButton_Click(object sender, RoutedEventArgs e)
        {
            termServ.Server = serverBox.Text;
            termServ.Connect();
        }
    }
}