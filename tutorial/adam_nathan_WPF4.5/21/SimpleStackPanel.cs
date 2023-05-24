using System;
using System.Windows;
using System.Windows.Controls;

namespace CustomPanels
{
  public class SimpleStackPanel : Panel
  {
    // The direction of stacking
    public static readonly DependencyProperty OrientationProperty = 
      DependencyProperty.Register("Orientation", typeof(Orientation),
      typeof(SimpleStackPanel), new FrameworkPropertyMetadata(Orientation.Vertical,
      FrameworkPropertyMetadataOptions.AffectsMeasure));

    public Orientation Orientation
    {
      get { return (Orientation)GetValue(OrientationProperty); }
      set { SetValue(OrientationProperty, value); }
    }

    protected override Size MeasureOverride(Size availableSize)
    {
      Size desiredSize = new Size();

      // Let children grow indefinitely in the direction of stacking,
      // overwriting what was passed in
      if (Orientation == Orientation.Vertical)
        availableSize.Height = Double.PositiveInfinity;
      else
        availableSize.Width = Double.PositiveInfinity;

      foreach (UIElement child in this.Children)
      {
          if (child != null)
          {
              // Ask the first child for its desired size, given unlimited space in
              // the direction of stacking and all our available space (whatever was
              // passed in) in the other direction
              child.Measure(availableSize);

              // Our desired size is the sum of child sizes in the direction of 
              // stacking, and the size of the largest child in the other direction
              if (Orientation == Orientation.Vertical)
              {
                  desiredSize.Width = Math.Max(desiredSize.Width,
                                               child.DesiredSize.Width);
                  desiredSize.Height += child.DesiredSize.Height;
              }
              else
              {
                  desiredSize.Height = Math.Max(desiredSize.Height,
                                                child.DesiredSize.Height);
                  desiredSize.Width += child.DesiredSize.Width;
              }
          }
      }

      return desiredSize;
    }

    protected override Size ArrangeOverride(Size finalSize)
    {
      double offset = 0;

      foreach (UIElement child in this.Children)
      {
          if (child != null)
          {
              if (Orientation == Orientation.Vertical)
              {
                  // The offset moves the child down the stack.
                  // Give the child all our width, but as much height as it desires.
                  child.Arrange(new Rect(0, offset, finalSize.Width,
                                                    child.DesiredSize.Height));

                  // Update the offset for the next child
                  offset += child.DesiredSize.Height;
              }
              else
              {
                  // The offset moves the child down the stack.
                  // Give the child all our height, but as much width as it desires.
                  child.Arrange(new Rect(offset, 0, child.DesiredSize.Width,
                                                    finalSize.Height));

                  // Update the offset for the next child
                  offset += child.DesiredSize.Width;
              }
          }
      }

      // Fill all the space given
      return finalSize;
    }
  }
}