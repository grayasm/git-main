using System.Windows;
using System.Windows.Input;

public partial class AboutDialog : Window
{
    public AboutDialog()
    {
        InitializeComponent();
    }

    void HelpCanExecute(object sender, CanExecuteRoutedEventArgs e)
    {
        e.CanExecute = true;
    }
    
    void HelpExecuted(object sender, ExecutedRoutedEventArgs e)
    {
        System.Diagnostics.Process.Start("http://www.adamnathan.net/wpf");
    }
}