using System;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;

namespace WpfDirectX
{
    // Three PInvoke signatures for communicating with the unmanaged C++ DirectX Sample DLL
    class Sample
    {
        [DllImport("DirectXSample.dll")]
        internal static extern IntPtr Initialize(IntPtr hwnd, int width, int height);

        [DllImport("DirectXSample.dll")]
        internal static extern void Render();

        [DllImport("DirectXSample.dll")]
        internal static extern void Cleanup();
    }

    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);
            // Now that we can get an HWND for the Window, force the initialization
            // that is otherwise done when the front buffer becomes available:
            d3dImage_IsFrontBufferAvailableChanged(this, new DependencyPropertyChangedEventArgs());
        }

        private void d3dImage_IsFrontBufferAvailableChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if (d3dImage.IsFrontBufferAvailable)
            {
                // (Re)initialization:
                IntPtr surface = Sample.Initialize(new WindowInteropHelper(this).Handle,
                    (int)this.Width, (int)this.Height);

                if (surface != IntPtr.Zero)
                {
                    d3dImage.Lock();
                    d3dImage.SetBackBuffer(D3DResourceType.IDirect3DSurface9, surface);
                    d3dImage.Unlock();

                    CompositionTarget.Rendering += CompositionTarget_Rendering;
                }
            }
            else
            {
                // Cleanup:
                CompositionTarget.Rendering -= CompositionTarget_Rendering;
                Sample.Cleanup();
            }
        }

        // Render the DirectX scene onto the D3DImage when WPF itself is ready to render
        private void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            if (d3dImage.IsFrontBufferAvailable)
            {
                d3dImage.Lock();
                Sample.Render();
                // Invalidate the whole area:
                d3dImage.AddDirtyRect(new Int32Rect(0, 0, d3dImage.PixelWidth, d3dImage.PixelHeight));
                d3dImage.Unlock();
            }
        }
    }
}
