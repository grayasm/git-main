using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace TouchEvents
{
    public partial class MainWindow : Window
    {
        // Keep track of which images are used for which TouchDevices
        Dictionary<TouchDevice, Image> fingerprints = new Dictionary<TouchDevice, Image>();
 
        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnTouchDown(TouchEventArgs e)
        {
            base.OnTouchDown(e);

            // Capture this touch device
            canvas.CaptureTouch(e.TouchDevice);

            // Create a new image for this new touch
            Image fingerprint = new Image { Source = new BitmapImage(new Uri("pack://application:,,,/fingerprint.png")) };

            // Move the image to the touch point
            TouchPoint point = e.GetTouchPoint(canvas);
            fingerprint.RenderTransform = new TranslateTransform(point.Position.X, point.Position.Y);

            // Keep track of the image and add it to the canvas
            fingerprints[e.TouchDevice] = fingerprint;
            canvas.Children.Add(fingerprint);
        }

        protected override void OnTouchMove(TouchEventArgs e)
        {
            base.OnTouchMove(e);

            if (e.TouchDevice.Captured == canvas)
            {
                // Retrieve the right image
                Image fingerprint = fingerprints[e.TouchDevice];
                TranslateTransform transform = fingerprint.RenderTransform as TranslateTransform;

                // Move it to the new location
                TouchPoint point = e.GetTouchPoint(canvas);
                transform.X = point.Position.X;
                transform.Y = point.Position.Y;
            }
        }

        protected override void OnTouchUp(TouchEventArgs e)
        {
            base.OnTouchUp(e);

            // Release capture
            canvas.ReleaseTouchCapture(e.TouchDevice);

            // Remove the image from the canvas and the dictionary
            canvas.Children.Remove(fingerprints[e.TouchDevice]);
            fingerprints.Remove(e.TouchDevice);
        }
    }
}