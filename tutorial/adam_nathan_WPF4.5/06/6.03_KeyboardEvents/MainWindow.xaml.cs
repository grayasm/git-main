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

namespace KeyboardEvents
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            this.KeyDown += OnKeyDown;
        }
        private void OnKeyDown(object sender, KeyEventArgs e)
        {
            if ((e.KeyboardDevice.Modifiers & ModifierKeys.Alt) == ModifierKeys.Alt &&
                 (e.Key == Key.A || e.SystemKey == Key.A))
            {
                // Alt+A has been pressed, potentially also with Ctrl,Shift and/or Windows
                MessageBox.Show("Alt + A was pressed!");
            }

            base.OnKeyDown(e);
        }
    }
}
