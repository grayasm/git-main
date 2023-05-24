using System;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;

namespace SpinThePrizeWheel
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            grid.ManipulationStarting        += Grid_ManipulationStarting;
            grid.ManipulationDelta           += Grid_ManipulationDelta;
            grid.ManipulationInertiaStarting += Grid_ManipulationInertiaStarting;
            grid.ManipulationCompleted       += Grid_ManipulationCompleted;
        }

        void Grid_ManipulationStarting(object sender, ManipulationStartingEventArgs e)
        {
            e.Mode = ManipulationModes.Rotate; // Only allow rotation
        }

        void Grid_ManipulationDelta(object sender, ManipulationDeltaEventArgs e)
        {
            (prizeWheel.RenderTransform as RotateTransform).Angle += e.DeltaManipulation.Rotation;
        }

        void Grid_ManipulationInertiaStarting(object sender, ManipulationInertiaStartingEventArgs e)
        {
            e.RotationBehavior.DesiredDeceleration = 0.001;
        }

        void Grid_ManipulationCompleted(object sender, ManipulationCompletedEventArgs e)
        {
            // Now that the wheel has stopped, tell the user what s/he won!
        }
    }
}