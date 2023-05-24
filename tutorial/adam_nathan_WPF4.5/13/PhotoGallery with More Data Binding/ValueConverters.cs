using System;
using System.Globalization;
using System.Windows.Data;
using System.Windows.Media;

namespace PhotoGallery
{
    public class CountToBackgroundConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter,
            CultureInfo culture)
        {
            if (targetType != typeof(Brush))
                throw new InvalidOperationException("The target must be a Brush!");

            // Let Parse throw an exception if the input is bad
            int num = int.Parse(value.ToString());

            return (num == 0 ? parameter : Brushes.Transparent);
        }
        public object ConvertBack(object value, Type targetType, object parameter,
            CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }

    public class RawCountToDescriptionConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter,
            CultureInfo culture)
        {
            // Let Parse throw an exception if the input is bad
            int num = int.Parse(value.ToString());
            return num + (num == 1 ? " item" : " items");
        }

        public object ConvertBack(object value, Type targetType, object parameter,
            CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }

    public class DateTimeToDateConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter,
           CultureInfo culture)
        {
            return ((DateTime)value).ToString("MM/dd/yyyy");
        }
    
        public object ConvertBack(object value, Type targetType, object parameter,
            CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}