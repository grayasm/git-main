using System.Windows.Media;
using System.Windows.Controls.Primitives;

namespace Chapter20
{
    public partial class PlayingCard : ToggleButton
    {
        public PlayingCard()
        {
            InitializeComponent();
        }

        public string Face
        {
            get { return face; }
            set { face = value; Foreground = (Brush)TryFindResource(face); }
        }

        private string face;
    }
}