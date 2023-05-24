using System;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;

namespace ManipulationEvents
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            canvas.ManipulationDelta += new EventHandler<ManipulationDeltaEventArgs>(Canvas_ManipulationDelta);
            canvas.ManipulationInertiaStarting += new EventHandler<ManipulationInertiaStartingEventArgs>(Canvas_ManipulationInertiaStarting);
        }

        void Canvas_ManipulationInertiaStarting(object sender, ManipulationInertiaStartingEventArgs e)
        {
            e.TranslationBehavior.DesiredDeceleration = 0.01;
            e.RotationBehavior.DesiredDeceleration = 0.01;
            e.ExpansionBehavior.DesiredDeceleration = 0.01;
        }

        void Canvas_ManipulationDelta(object sender, ManipulationDeltaEventArgs e)
        {
            MatrixTransform transform = photo.RenderTransform as MatrixTransform;
            if (transform != null)
            {
                // Apply any deltas to the matrix, then apply the new Matrix as the MatrixTransform data:
                Matrix matrix = transform.Matrix;
                matrix.Translate(e.DeltaManipulation.Translation.X, e.DeltaManipulation.Translation.Y);
                matrix.RotateAt(e.DeltaManipulation.Rotation, e.ManipulationOrigin.X, e.ManipulationOrigin.Y);
                matrix.ScaleAt(e.DeltaManipulation.Scale.X, e.DeltaManipulation.Scale.Y, e.ManipulationOrigin.X, e.ManipulationOrigin.Y);
                transform.Matrix = matrix;
                e.Handled = true;
            }
        }
    }
}