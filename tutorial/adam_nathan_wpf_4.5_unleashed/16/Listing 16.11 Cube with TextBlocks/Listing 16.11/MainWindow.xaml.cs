using System;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Media3D;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        CompositionTarget.Rendering += CompositionTarget_Rendering;
    }

    static TimeSpan lastRenderTime = new TimeSpan();

    void CompositionTarget_Rendering(object sender, EventArgs e)
    {
        // Ensure we only do this once per frame
        if (lastRenderTime == ((RenderingEventArgs)e).RenderingTime)
            return;

        lastRenderTime = ((RenderingEventArgs)e).RenderingTime;

        GeneralTransform3DTo2D transform = Cube.TransformToAncestor(myGrid);

        Point p = transform.Transform(new Point3D(-1, -1, -1));
        t_000.X = p.X; t_000.Y = p.Y;

        p = transform.Transform(new Point3D(-1, -1, 1));
        t_001.X = p.X; t_001.Y = p.Y;

        p = transform.Transform(new Point3D(-1, 1, -1));
        t_010.X = p.X; t_010.Y = p.Y;

        p = transform.Transform(new Point3D(-1, 1, 1));
        t_011.X = p.X; t_011.Y = p.Y;

        p = transform.Transform(new Point3D(1, -1, -1));
        t_100.X = p.X; t_100.Y = p.Y;

        p = transform.Transform(new Point3D(1, -1, 1));
        t_101.X = p.X; t_101.Y = p.Y;

        p = transform.Transform(new Point3D(1, 1, -1));
        t_110.X = p.X; t_110.Y = p.Y;

        p = transform.Transform(new Point3D(1, 1, 1));
        t_111.X = p.X; t_111.Y = p.Y;
    }
}