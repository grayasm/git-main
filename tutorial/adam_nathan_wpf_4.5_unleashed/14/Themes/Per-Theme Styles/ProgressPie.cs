using System.Windows;
using System.Windows.Controls;

namespace ThemedProgressPie
{
    public class ProgressPie : ProgressBar
    {
        static ProgressPie()
        {
            DefaultStyleKeyProperty.OverrideMetadata(
            typeof(ProgressPie),
            new FrameworkPropertyMetadata(typeof(ProgressPie)));
        }
    }
}