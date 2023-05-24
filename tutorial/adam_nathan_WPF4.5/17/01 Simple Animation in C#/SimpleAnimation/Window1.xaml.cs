using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;

public partial class Window1 : Window
{
    public Window1()
    {
        InitializeComponent();

        // Define the animation
        DoubleAnimation a = new DoubleAnimation();
        a.From = 50;
        a.To = 100;

        // Start animating
        b.BeginAnimation(Button.WidthProperty, a);
    }
}