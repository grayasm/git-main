using System.Windows;
using System.Windows.Input;

public partial class GadgetWindow : Window
{
  public GadgetWindow()
  {
    InitializeComponent();
  }
  void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
  {
    this.DragMove();
  }
  void Button_Click(object sender, RoutedEventArgs e)
  {
      this.Close();
  }
}