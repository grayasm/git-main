using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace CustomPanels
{
    public class SimpleCanvas : Panel
    {
        public static readonly DependencyProperty LeftProperty
            = DependencyProperty.RegisterAttached("Left", typeof(double), typeof(SimpleCanvas),
                    new FrameworkPropertyMetadata(Double.NaN, FrameworkPropertyMetadataOptions.AffectsParentArrange));

        public static readonly DependencyProperty TopProperty
            = DependencyProperty.RegisterAttached("Top", typeof(double), typeof(SimpleCanvas),
                    new FrameworkPropertyMetadata(Double.NaN, FrameworkPropertyMetadataOptions.AffectsParentArrange));
        
        [TypeConverter(typeof(LengthConverter)), AttachedPropertyBrowsableForChildren]
        public static double GetLeft(UIElement element)
        {
            if (element == null) { throw new ArgumentNullException("element"); }
            return (double)element.GetValue(LeftProperty);
        }

        [TypeConverter(typeof(LengthConverter)), AttachedPropertyBrowsableForChildren]
        public static void SetLeft(UIElement element, double length)
        {
            if (element == null) { throw new ArgumentNullException("element"); }
            element.SetValue(LeftProperty, length);
        }

        [TypeConverter(typeof(LengthConverter)), AttachedPropertyBrowsableForChildren]
        public static double GetTop(UIElement element)
        {
            if (element == null) { throw new ArgumentNullException("element"); }
            return (double)element.GetValue(TopProperty);
        }

        [TypeConverter(typeof(LengthConverter)), AttachedPropertyBrowsableForChildren]
        public static void SetTop(UIElement element, double length)
        {
            if (element == null) { throw new ArgumentNullException("element"); }
            element.SetValue(TopProperty, length);
        }

        protected override Size MeasureOverride(Size availableSize)
        {
            foreach (UIElement child in this.Children)
            {
                // Give each child all the space it wants
                if (child != null)
                    child.Measure(new Size(Double.PositiveInfinity, Double.PositiveInfinity));
            }

            // The SimpleCanvas itself needs no space
            return new Size(0, 0);
        }

        protected override Size ArrangeOverride(Size finalSize)
        {
            foreach (UIElement child in this.Children)
            {
                if (child != null)
                {
                    double x = 0;
                    double y = 0;

                    // Respect any Left and Top attached properties,
                    // otherwise the child is placed at (0,0)
                    double left = GetLeft(child);
                    if (!Double.IsNaN(left))
                        x = left;

                    double top = GetTop(child);
                    if (!Double.IsNaN(top))
                        y = top;

                    // Place at the chosen (x,y) location with the child's DesiredSize
                    child.Arrange(new Rect(new Point(x, y), child.DesiredSize));
                }
            }

            // Whatever size you gave me is fine
            return finalSize;
        }
    }
}