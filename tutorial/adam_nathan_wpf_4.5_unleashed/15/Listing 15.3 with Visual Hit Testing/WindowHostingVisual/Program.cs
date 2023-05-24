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
            whv.ShowDialog();
        }
    }
}
