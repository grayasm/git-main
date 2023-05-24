using System.Windows;
using System.Windows.Controls;

public partial class AboutDialog : Window
{
    public AboutDialog()
    {
        InitializeComponent();
    }

    void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
    {
        if (e.AddedItems.Count > 0)
            MessageBox.Show("You just selected " + e.AddedItems[0]);
    }

    void Button_Click(object sender, RoutedEventArgs e)
    {
        MessageBox.Show("You just clicked " + e.Source);
    }
}