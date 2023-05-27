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

namespace DependencyPropertyApp
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
    }


    // A Standard Dependency Property Implementation
    public class BButton : DependencyObject
    {
        // the dependency property
        public static readonly DependencyProperty IsDefaultProperty;

        static BButton()
        {
            // register the property
            BButton.IsDefaultProperty = 
                DependencyProperty.Register("IsDefault", typeof(bool), typeof(BButton),
                    new FrameworkPropertyMetadata(false, new PropertyChangedCallback(OnIsDefaultChanged)));
        }

        // a .NET property wrapper (optional)
        public bool IsDefault
        {
            get { return (bool)GetValue(BButton.IsDefaultProperty); }
            set { SetValue(BButton.IsDefaultProperty, value); }
        }

        // a property changed callback (optional)
        private static void OnIsDefaultChanged(DependencyObject o, DependencyPropertyChangedEventArgs e) 
        {
        }
    }
}
