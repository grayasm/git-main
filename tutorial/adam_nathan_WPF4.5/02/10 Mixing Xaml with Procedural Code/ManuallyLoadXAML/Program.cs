using System;
using System.IO;
using System.Windows;
using System.Windows.Markup;
using System.Windows.Controls;

namespace MyNamespace
{
    class Program
    {
        [STAThread]
        public static void Main()
        {
            Window window = null;
            using (FileStream fs =
            new FileStream("MyWindow.xaml", FileMode.Open, FileAccess.Read))
            {
                // Get the root element, which we know is a Window
                window = (Window)XamlReader.Load(fs);
            }
            // Grab the OK button, knowing only its name
            Button okButton = (Button)window.FindName("okButton");

            // Display the Window
            window.Show();

            // Show the Button's Content
            MessageBox.Show(okButton.Content.ToString());

            // Immediately exit (see Chapter 7)
        }
    }
}