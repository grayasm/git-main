using System;
using System.Windows;
using System.Windows.Media;

namespace WindowHostingVisual
{
    public class WindowHostingVisual : Window
    {
        DrawingVisual ghostVisual = null;

        public WindowHostingVisual()
        {
            Title = "Hosting DrawingVisuals";
            Width = 300;
            Height = 350;

            ghostVisual = new DrawingVisual();
            using (DrawingContext dc = ghostVisual.RenderOpen())
            {
                // The body
                dc.DrawGeometry(Brushes.Blue, null, Geometry.Parse(
                @"M 240,250
                  C 200,375 200,250 175,200
                  C 100,400 100,250 100,200
                  C 0,350 0,250 30,130
                  C 75,0 100,0 150,0
                  C 200,0 250,0 250,150 Z"));
                // Left eye
                dc.DrawEllipse(Brushes.Black, new Pen(Brushes.White, 10),
                    new Point(95, 95), 15, 15);
                // Right eye
                dc.DrawEllipse(Brushes.Black, new Pen(Brushes.White, 10),
                    new Point(170, 105), 15, 15);
                // The mouth
                Pen p = new Pen(Brushes.Black, 10);
                p.StartLineCap = PenLineCap.Round;
                p.EndLineCap = PenLineCap.Round;
                dc.DrawLine(p, new Point(75, 160), new Point(175, 150));
            }
            // Bookkeeping:
            AddVisualChild(ghostVisual);
            AddLogicalChild(ghostVisual);
        }

        // The two necessary overrides, implemented for the single Visual:
        protected override int VisualChildrenCount
        {
            get { return 1; }
        }

        protected override Visual GetVisualChild(int index)
        {
            if (index != 0)
                throw new ArgumentOutOfRangeException("index");
            return ghostVisual;
        }
    }
}