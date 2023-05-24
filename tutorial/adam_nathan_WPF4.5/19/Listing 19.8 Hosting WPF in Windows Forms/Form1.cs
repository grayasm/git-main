using System.Windows.Forms;
using System.Windows.Controls;

namespace WindowsFormsHostingWPF
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // Create a WPF Expander
            Expander expander = new Expander();
            expander.Header = "WPF Expander";
            expander.Content = "Content";

            // Add it to the ElementHost
            elementHost.Child = expander;
        }
    }
}