using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Media.Media3D;

namespace House3D
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>

    public partial class Window1 : System.Windows.Window
    {

        public Window1()
        {
        }

        private void MouseDownHandler(object sender,
          System.Windows.Input.MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            Viewport3D viewport = (Viewport3D)sender;
            Point location = e.GetPosition(viewport);

            HitTestResult result = VisualTreeHelper.HitTest(viewport, location);

            if (result != null && result.VisualHit is Visual3D)
            {
                RayMeshGeometry3DHitTestResult result3D = result as RayMeshGeometry3DHitTestResult;

                if (result3D != null)
                {
                    MessageBox.Show(String.Format(@"Visual3D Hit -- Information:

VisualHit: {0}
ModelHit: {1}
MeshHit: {2}
DistanceToRayOrigin: {3}
PointHit: {4} (In space of VisualHit)
VertexIndices: {5},{6},{7}
VertexWeights: {8},{9},{10}
PointHit: {11} (In space of MeshHit)
UV: {12}",
                    result3D.VisualHit,
                    result3D.ModelHit,
                    result3D.MeshHit,
                    result3D.DistanceToRayOrigin,
                    result3D.PointHit,
                    result3D.VertexIndex1, result3D.VertexIndex2, result3D.VertexIndex3,
                    result3D.VertexWeight1, result3D.VertexWeight2, result3D.VertexWeight3,
                    GetMeshPointHit(result3D),
                    GetUV(result3D)));
                }
            }
        }

        private Point GetUV(RayMeshGeometry3DHitTestResult result3D)
        {
            int limit = result3D.MeshHit.TextureCoordinates.Count;

            if (result3D.VertexIndex1 < limit
                && result3D.VertexIndex2 < limit
                && result3D.VertexIndex3 < limit)
            {
                return Interpolate(result3D.VertexWeight1, result3D.VertexWeight2, result3D.VertexWeight3,
                    result3D.MeshHit.TextureCoordinates[result3D.VertexIndex1],
                    result3D.MeshHit.TextureCoordinates[result3D.VertexIndex2],
                    result3D.MeshHit.TextureCoordinates[result3D.VertexIndex3]);
            }

            return new Point(double.NaN, double.NaN);
        }

        private Point Interpolate(double w1, double w2, double w3, Point p1, Point p2, Point p3)
        {
            return new Point(
                p1.X * w1 + p2.X * w2 + p3.X * w3,
                p1.Y * w1 + p2.Y * w2 + p3.Y * w3);
        }

        private Point3D GetMeshPointHit(RayMeshGeometry3DHitTestResult result3D)
        {
            return Interpolate(result3D.VertexWeight1, result3D.VertexWeight2, result3D.VertexWeight3,
                result3D.MeshHit.Positions[result3D.VertexIndex1],
                result3D.MeshHit.Positions[result3D.VertexIndex2],
                result3D.MeshHit.Positions[result3D.VertexIndex3]);
        }

        private Point3D Interpolate(double w1, double w2, double w3, Point3D p1, Point3D p2, Point3D p3)
        {
            return new Point3D(
                p1.X * w1 + p2.X * w2 + p3.X * w3,
                p1.Y * w1 + p2.Y * w2 + p3.Y * w3,
                p1.Z * w1 + p2.Z * w2 + p3.Z * w3);
        }
    }
}