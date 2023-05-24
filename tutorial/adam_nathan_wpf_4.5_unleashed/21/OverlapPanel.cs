using System;
using System.Windows;
using System.Windows.Controls;

namespace CustomPanels
{
    public class OverlapPanel : Panel
    {
        double _totalChildrenSize = 0; /**********/

        // The direction of stacking
        public static readonly DependencyProperty OrientationProperty =
          DependencyProperty.Register("Orientation", typeof(Orientation),
          typeof(OverlapPanel), new FrameworkPropertyMetadata(Orientation.Vertical,
          FrameworkPropertyMetadataOptions.AffectsMeasure));

        public Orientation Orientation
        {
            get { return (Orientation)GetValue(OrientationProperty); }
            set { SetValue(OrientationProperty, value); }
        }

        protected override Size MeasureOverride(Size availableSize)
        {
            Size desiredSize = new Size();

            foreach (UIElement child in this.Children)
            {
                if (child != null)
                {
                    /************/
                    // See how big each child wants to be given all our available space
                    child.Measure(availableSize);
                    /************/

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

            _totalChildrenSize = (Orientation == Orientation.Vertical ? desiredSize.Height : desiredSize.Width); /************/

            return desiredSize;
        }

        protected override Size ArrangeOverride(Size finalSize)
        {
            double offset = 0;
            /************/
            double overlap = 0;

            // Figure out the amount of overlap by seeing how much less space we got than desired,
            // and divide it equally among children.
            if (Orientation == Orientation.Vertical)
            {
                if (finalSize.Height > _totalChildrenSize)
                    // If we're given more than _totalChildrenSize, the negative overlap represents how much the layout should stretch
                    overlap = (_totalChildrenSize - finalSize.Height) / this.Children.Count;
                else
                    // In this case, this.DesiredSize gives us the actual smaller size
                    overlap = (_totalChildrenSize - this.DesiredSize.Height) / this.Children.Count;
            }
            else
            {
                if (finalSize.Width > _totalChildrenSize)
                    // If we're given more than _totalChildrenSize, the negative overlap represents how much the layout should stretch
                    overlap = (_totalChildrenSize - finalSize.Width) / this.Children.Count;
                else
                    // In this case, this.DesiredSize gives us the actual smaller size
                    overlap = (_totalChildrenSize - this.DesiredSize.Width) / this.Children.Count;
            }
            /************/

            foreach (UIElement child in this.Children)
            {
                if (child != null)
                {
                    if (Orientation == Orientation.Vertical)
                    {
                        // The offset moves the child down the stack.
                        // Give the child all our width, but as much height as it desires
                        // or more if there is negative overlap /**********/
                        child.Arrange(new Rect(0, offset, finalSize.Width,
                                                          child.DesiredSize.Height + (overlap > 0 ? 0 : -overlap)));

                        // Update the offset for the next child
                        offset += (child.DesiredSize.Height - overlap); /************/
                    }
                    else
                    {
                        // The offset moves the child down the stack.
                        // Give the child all our height, but as much width as it desires
                        // or more if there is negative overlap /**********/
                        child.Arrange(new Rect(offset, 0, child.DesiredSize.Width + (overlap > 0 ? 0 : -overlap),
                                                          finalSize.Height));

                        // Update the offset for the next child
                        offset += (child.DesiredSize.Width - overlap); /************/
                    }
                }
            }

            // Fill all the space given
            return finalSize;
        }
    }
}