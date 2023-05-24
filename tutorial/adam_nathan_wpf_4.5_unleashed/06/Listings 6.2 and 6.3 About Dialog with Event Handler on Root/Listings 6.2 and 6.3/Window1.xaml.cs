using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Controls;

public partial class AboutDialog : Window
{
    public AboutDialog()
    {
        InitializeComponent();
    }

    void AboutDialog_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
    {
        // Display information about this event
        this.Title = "Source = " + e.Source.GetType().Name + ", OriginalSource = " +
        e.OriginalSource.GetType().Name + " @ " + e.Timestamp;

        // In this example, all possible sources derive from Control
        Control source = e.Source as Control;

        // Toggle the border on the source control
        if (source.BorderThickness != new Thickness(5))
        {
            source.BorderThickness = new Thickness(5);
            source.BorderBrush = Brushes.Black;
        }
        else
            source.BorderThickness = new Thickness(0);
    }
}