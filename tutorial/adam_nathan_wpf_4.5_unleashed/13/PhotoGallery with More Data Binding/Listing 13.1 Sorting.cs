using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Data;

namespace PhotoGallery
{
    partial class MainWindow
    {
        // Click event handlers for three different Buttons:
        void sortByName_Click(object sender, RoutedEventArgs e)
        {
            SortHelper("Name");
        }
        void sortByDateTime_Click(object sender, RoutedEventArgs e)
        {
            SortHelper("DateTime");
        }
        void sortBySize_Click(object sender, RoutedEventArgs e)
        {
            SortHelper("Size");
        }

        void SortHelper(string propertyName)
        {
            // Get the default view
            ICollectionView view = CollectionViewSource.GetDefaultView(photos);

            // Check if the view is already sorted ascending by the current property
            if (view.SortDescriptions.Count > 0
                && view.SortDescriptions[0].PropertyName == propertyName
                && view.SortDescriptions[0].Direction == ListSortDirection.Ascending)
            {
                // Already sorted ascending, so "toggle" by sorting descending
                view.SortDescriptions.Clear();
                view.SortDescriptions.Add(new SortDescription(
                    propertyName, ListSortDirection.Descending));
            }
            else
            {
                // Sort ascending
                view.SortDescriptions.Clear();
                view.SortDescriptions.Add(new SortDescription(
                   propertyName, ListSortDirection.Ascending));
            }
        }
    }
}