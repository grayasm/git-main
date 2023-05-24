using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace CustomPanels
{
    public class FanCanvas : Panel
    {
        public static readonly DependencyProperty OrientationProperty =
          DependencyProperty.Register("Orientation", typeof(Orientation),
          typeof(FanCanvas), new FrameworkPropertyMetadata(Orientation.Horizontal,
          FrameworkPropertyMetadataOptions.AffectsArrange));

        public static readonly DependencyProperty SpacingProperty =
          DependencyProperty.Register("Spacing", typeof(double),
          typeof(FanCanvas), new FrameworkPropertyMetadata(10d,
          FrameworkPropertyMetadataOptions.AffectsArrange));

        public static readonly DependencyProperty AngleIncrementProperty =
          DependencyProperty.Register("AngleIncrement", typeof(double),
          typeof(FanCanvas), new FrameworkPropertyMetadata(10d,
          FrameworkPropertyMetadataOptions.AffectsArrange));

        public Orientation Orientation
        {
            get { return (Orientation)GetValue(OrientationProperty); }
            set { SetValue(OrientationProperty, value); }
        }

        public double Spacing
        {
            get { return (double)GetValue(SpacingProperty); }
            set { SetValue(SpacingProperty, value); }
        }

        public double AngleIncrement
        {
            get { return (double)GetValue(AngleIncrementProperty); }
            set { SetValue(AngleIncrementProperty, value); }
        }

        protected override Size MeasureOverride(Size availableSize)
        {
            foreach (UIElement child in this.Children)
            {
                // Give each child all the space it wants
                if (child != null)
                    child.Measure(new Size(Double.PositiveInfinity,
                                           Double.PositiveInfinity));
            }

            // The SimpleCanvas itself needs no space
            return new Size(0, 0);
        }


        protected override Size ArrangeOverride(Size finalSize)
        {
            // Center the children
            Point location = new Point(0,0);
            double angle = GetStartingAngle();

            foreach (UIElement child in this.Children)
            {
                if (child != null)
                {
                    // Give the child its desired size
                    child.Arrange(new Rect(location, child.DesiredSize));

                    // WARNING: Overwrite any RenderTransform with one that
                    //          arranges children in the fan shape
                    child.RenderTransform = new RotateTransform(angle, child.RenderSize.Width / 2, child.RenderSize.Height);

                    // Update the offset and angle for the next child
                    if (Orientation == Orientation.Vertical)
                        location.Y += Spacing;
                    else
                        location.X += Spacing;

                    angle += AngleIncrement;
                }
            }

            // Fill all the space given
            return finalSize;
        }

        double GetStartingAngle()
        {
            double angle;

            if (this.Children.Count % 2 != 0)
                // Odd, so the middle child will have angle == 0
                angle = -AngleIncrement * (this.Children.Count / 2);
            else
                // Even, so the middle two children will be half of the AngleIncrement on either side of 0
                angle = -AngleIncrement * (this.Children.Count / 2) + AngleIncrement / 2;

            // Rotate 90 degrees if vertical
            if (Orientation == Orientation.Vertical)
                angle += 90;

            return angle;
        }
    }
}