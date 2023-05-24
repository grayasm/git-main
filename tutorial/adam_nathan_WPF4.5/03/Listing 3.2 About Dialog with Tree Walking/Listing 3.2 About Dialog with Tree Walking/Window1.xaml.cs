using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Media;

public partial class AboutDialog : Window
{
    public AboutDialog()
    {
        InitializeComponent();
        PrintLogicalTree(0, this);
    }

    protected override void OnContentRendered(EventArgs e)
    {
        base.OnContentRendered(e);
        PrintVisualTree(0, this);
    }
    
    void PrintLogicalTree(int depth, object obj)
    {
        // Print the object with preceding spaces that represent its depth
        Debug.WriteLine(new string(' ', depth) + obj);
        // Sometimes leaf nodes aren’t DependencyObjects (e.g. strings)
        if (!(obj is DependencyObject)) return;
        // Recursive call for each logical child
        foreach (object child in LogicalTreeHelper.GetChildren(
        obj as DependencyObject))
            PrintLogicalTree(depth + 1, child);
    }

    void PrintVisualTree(int depth, DependencyObject obj)
    {
        // Print the object with preceding spaces that represent its depth
        Debug.WriteLine(new string(' ', depth) + obj);
        // Recursive call for each visual child
        for (int i = 0; i < VisualTreeHelper.GetChildrenCount(obj); i++)
            PrintVisualTree(depth + 1, VisualTreeHelper.GetChild(obj, i));
    }
}