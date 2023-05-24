using System;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;

public partial class MainWindow : Window
{
    static Random r;

    public MainWindow()
    {
        InitializeComponent();
        r = new Random();
    }

    private void Cube_MouseDown(object sender, MouseButtonEventArgs e)
    {
        CubeBrush.Color = Color.FromRgb((byte)r.Next(), (byte)r.Next(), (byte)r.Next());
    }
}