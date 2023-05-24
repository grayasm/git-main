using System;
using System.Windows;
using System.Windows.Media;
using System.Windows.Navigation;

namespace PhotoGallery
{
    [Serializable]
    class RotateState : CustomContentState
    {
        FrameworkElement element;
        double rotation;
 
        public RotateState(FrameworkElement element, double rotation)
        {
            this.element = element;
            this.rotation = rotation;
        }
        
        public override string JournalEntryName
        {
            get { return "Rotate " + rotation + "°"; }
        }
        
        public override void Replay(NavigationService navigationService, NavigationMode mode)
        {
            // Rotate the element by the specified amount
            element.LayoutTransform = new RotateTransform(rotation);
        }
    }
}