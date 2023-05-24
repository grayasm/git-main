using System;
using System.Windows;

namespace WindowHostingVisual
{
    class Program
    {
        [STAThread]
        public static void Main()
        {
            WindowHostingVisual whv = new WindowHostingVisual();
            MessageBox.Show("The DrawingVisual still needs to be rendered.  This is done in the next listing.");
            whv.ShowDialog();
        }
    }
}
