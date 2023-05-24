using System;
using System.Windows;

namespace WindowsApplication1
{
    public partial class Window1 : Window
    {
        int currentSkin = 0;

        public Window1()
        {
            InitializeComponent();
        }

        void Cancel_Click(object sender, RoutedEventArgs e)
        {
            ResourceDictionary resources = null;
            currentSkin = (currentSkin + 1) % 2;

            if (currentSkin == 0)
                resources = (ResourceDictionary)Application.LoadComponent(new Uri("LightAndFluffySkin.xaml", UriKind.RelativeOrAbsolute));
            else
                resources = (ResourceDictionary)Application.LoadComponent(new Uri("ElectricSkin.xaml", UriKind.RelativeOrAbsolute));

            Application.Current.Resources = resources;
        }
    }
}