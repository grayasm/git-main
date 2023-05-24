using System;
using System.Windows;
using System.Windows.Markup;
using System.Windows.Controls;
using System.IO;

namespace MyNamespace
{
    public partial class MyWindow : System.Windows.Window
    {
        public MyWindow()
        {
            // Necessary to call in order to load XAML-defined content!
            InitializeComponent();
        }
    }
}