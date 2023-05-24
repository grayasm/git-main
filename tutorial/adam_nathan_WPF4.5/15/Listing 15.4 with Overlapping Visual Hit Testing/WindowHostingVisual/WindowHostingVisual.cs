using System;
using System.Windows;
using System.Windows.Media;
using System.Collections.Generic;
using System.Windows.Input;

namespace WindowHostingVisual
{
    public class WindowHostingVisual : Window
    {
        List<Visual> visuals = new List<Visual>();

        public WindowHostingVisual()
        {
            Title = "Hosting DrawingVisuals";
            Width = 300;
            Height = 350;

            DrawingVisual bodyVisual = new DrawingVisual();
            DrawingVisual eyesVisual = new DrawingVisual();
            DrawingVisual mouthVisual = new DrawingVisual();

            using (DrawingContext dc = bodyVisual.RenderOpen())
            {
                // The body
                dc.DrawGeometry(Brushes.Blue, null, Geometry.Parse(
                @"M 240,250
              C 200,375 200,250 175,200
              C 100,400 100,250 100,200
              C 0,350 0,250 30,130
              C 75,0 100,0 150,0
              C 200,0 250,0 250,150 Z"));
            }
            using (DrawingContext dc = eyesVisual.RenderOpen())
            {
                // Left eye
                dc.DrawEllipse(Brushes.Black, new Pen(Brushes.White, 10),
                  new Point(95, 95), 15, 15);
                // Right eye
                dc.DrawEllipse(Brushes.Black, new Pen(Brushes.White, 10),
                 new Point(170, 105), 15, 15);
            }
            using (DrawingContext dc = mouthVisual.RenderOpen())
            {
                // The mouth
                Pen p = new Pen(Brushes.Black, 10);
                p.StartLineCap = PenLineCap.Round;
                p.EndLineCap = PenLineCap.Round;
                dc.DrawLine(p, new Point(75, 160), new Point(175, 150));
            }

            visuals.Add(bodyVisual);
            visuals.Add(eyesVisual);
            visuals.Add(mouthVisual);

            // Bookkeeping:
            foreach (Visual v in visuals)
            {
                AddVisualChild(v);
                AddLogicalChild(v);
            }
        }

        // The two necessary overrides, implemented for the single Visual:
        protected override int VisualChildrenCount
        {
            get { return visuals.Count; }
        }
        protected override Visual GetVisualChild(int index)
        {
            if (index < 0 || index >= visuals.Count)
                throw new ArgumentOutOfRangeException("index");
            return visuals[index];
        }

        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            // Retrieve the mouse pointer location relative to the Window
            Point location = e.GetPosition(this);

            // Perform visual hit testing
            VisualTreeHelper.HitTest(this, null,
                new HitTestResultCallback(HitTestCallback),
                new PointHitTestParameters(location));
        }

        public HitTestResultBehavior HitTestCallback(HitTestResult result)
        {
            // If we hit any DrawingVisual, rotate it
            if (result.VisualHit.GetType() == typeof(DrawingVisual))
            {
                DrawingVisual dv = result.VisualHit as DrawingVisual;
                if (dv.Transform == null)
                    dv.Transform = new RotateTransform();

                (dv.Transform as RotateTransform).Angle++;
            }
            // Keep looking for hits
            return HitTestResultBehavior.Continue;
        }
    }
}