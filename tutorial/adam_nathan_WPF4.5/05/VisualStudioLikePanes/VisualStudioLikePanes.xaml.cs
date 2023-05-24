using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

public partial class MainWindow : Window
{
    // Dummy columns for layers 0 and 1:
    ColumnDefinition column1CloneForLayer0;
    ColumnDefinition column2CloneForLayer0;
    ColumnDefinition column2CloneForLayer1;

    public MainWindow()
    {
        InitializeComponent();

        // Initialize the dummy columns used when docking:
        column1CloneForLayer0 = new ColumnDefinition();
        column1CloneForLayer0.SharedSizeGroup = "column1";
        column2CloneForLayer0 = new ColumnDefinition();
        column2CloneForLayer0.SharedSizeGroup = "column2";
        column2CloneForLayer1 = new ColumnDefinition();
        column2CloneForLayer1.SharedSizeGroup = "column2";
    }

    // Toggle between docked and undocked states (Pane 1)
    public void pane1Pin_Click(object sender, RoutedEventArgs e)
    {
        if (pane1Button.Visibility == Visibility.Collapsed)
            UndockPane(1);
        else
            DockPane(1);
    }

    // Toggle between docked and undocked states (Pane 2)
    public void pane2Pin_Click(object sender, RoutedEventArgs e)
    {
        if (pane2Button.Visibility == Visibility.Collapsed)
            UndockPane(2);
        else
            DockPane(2);
    }

    // Show Pane 1 when hovering over its button
    public void pane1Button_MouseEnter(object sender, RoutedEventArgs e)
    {
        layer1.Visibility = Visibility.Visible;

        // Adjust Z order to ensure the pane is on top:
        parentGrid.Children.Remove(layer1);
        parentGrid.Children.Add(layer1);

        // Ensure the other pane is hidden if it is undocked
        if (pane2Button.Visibility == Visibility.Visible)
            layer2.Visibility = Visibility.Collapsed;
    }

    // Show Pane 2 when hovering over its button
    public void pane2Button_MouseEnter(object sender, RoutedEventArgs e)
    {
        layer2.Visibility = Visibility.Visible;

        // Adjust Z order to ensure the pane is on top:
        parentGrid.Children.Remove(layer2);
        parentGrid.Children.Add(layer2);

        // Ensure the other pane is hidden if it is undocked
        if (pane1Button.Visibility == Visibility.Visible)
            layer1.Visibility = Visibility.Collapsed;
    }

    // Hide any undocked panes when the mouse enters Layer 0
    public void layer0_MouseEnter(object sender, RoutedEventArgs e)
    {
        if (pane1Button.Visibility == Visibility.Visible)
            layer1.Visibility = Visibility.Collapsed;
        if (pane2Button.Visibility == Visibility.Visible)
            layer2.Visibility = Visibility.Collapsed;
    }

    // Hide the other pane if undocked when the mouse enters Pane 1
    public void pane1_MouseEnter(object sender, RoutedEventArgs e)
    {
        // Ensure the other pane is hidden if it is undocked
        if (pane2Button.Visibility == Visibility.Visible)
            layer2.Visibility = Visibility.Collapsed;
    }

    // Hide the other pane if undocked when the mouse enters Pane 2
    public void pane2_MouseEnter(object sender, RoutedEventArgs e)
    {
        // Ensure the other pane is hidden if it is undocked
        if (pane1Button.Visibility == Visibility.Visible)
            layer1.Visibility = Visibility.Collapsed;
    }

    // Docks a pane, which hides the corresponding pane button
    public void DockPane(int paneNumber)
    {
        if (paneNumber == 1)
        {
            pane1Button.Visibility = Visibility.Collapsed;
            pane1PinImage.Source = new BitmapImage(new Uri("pin.gif", UriKind.Relative));

            // Add the cloned column to layer 0:
            layer0.ColumnDefinitions.Add(column1CloneForLayer0);
            // Add the cloned column to layer 1, but only if pane 2 is docked:
            if (pane2Button.Visibility == Visibility.Collapsed) layer1.ColumnDefinitions.Add(column2CloneForLayer1);
        }
        else if (paneNumber == 2)
        {
            pane2Button.Visibility = Visibility.Collapsed;
            pane2PinImage.Source = new BitmapImage(new Uri("pin.gif", UriKind.Relative));

            // Add the cloned column to layer 0:
            layer0.ColumnDefinitions.Add(column2CloneForLayer0);
            // Add the cloned column to layer 1, but only if pane 1 is docked:
            if (pane1Button.Visibility == Visibility.Collapsed) layer1.ColumnDefinitions.Add(column2CloneForLayer1);
        }
    }

    // Undocks a pane, which reveals the corresponding pane button
    public void UndockPane(int paneNumber)
    {
        if (paneNumber == 1)
        {
            layer1.Visibility = Visibility.Collapsed;
            pane1Button.Visibility = Visibility.Visible;
            pane1PinImage.Source = new BitmapImage(new Uri("pinHorizontal.gif", UriKind.Relative));

            // Remove the cloned columns from layers 0 and 1:
            layer0.ColumnDefinitions.Remove(column1CloneForLayer0);
            // This won't always be present, but Remove silently ignores bad columns:
            layer1.ColumnDefinitions.Remove(column2CloneForLayer1);
        }
        else if (paneNumber == 2)
        {
            layer2.Visibility = Visibility.Collapsed;
            pane2Button.Visibility = Visibility.Visible;
            pane2PinImage.Source = new BitmapImage(new Uri("pinHorizontal.gif", UriKind.Relative));

            // Remove the cloned columns from layers 0 and 1:
            layer0.ColumnDefinitions.Remove(column2CloneForLayer0);
            // This won't always be present, but Remove silently ignores bad columns:
            layer1.ColumnDefinitions.Remove(column2CloneForLayer1);
        }
    }
}