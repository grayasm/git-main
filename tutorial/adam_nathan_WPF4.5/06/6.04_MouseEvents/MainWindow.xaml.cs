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

namespace MouseEvents
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            this.MouseDown += OnMouseDown;
            this.MouseMove += OnMouseMove;
            this.MouseUp += OnMouseUp;
        }

        private void OnMouseDown(object sender, MouseEventArgs e)
        {
            MessageBox.Show("OnMouseDown");
        }
        private void OnMouseMove(object sender, MouseEventArgs e)
        {
            Point pos = e.GetPosition(this);
            position.Content = "Mouse position " + "X=" + pos.X + " Y=" + pos.Y;
        }
        private void OnMouseUp(object sender, MouseEventArgs e)
        {
            MessageBox.Show("OnMouseUp");
        }
    }
}
