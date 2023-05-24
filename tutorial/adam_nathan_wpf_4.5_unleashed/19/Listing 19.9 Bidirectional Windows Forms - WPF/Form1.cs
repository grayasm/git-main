using System.Windows.Forms;
using System.Windows.Controls;
using System.Windows.Forms.Integration;

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
            
            // Create a MonthCalendar and wrap it in a WindowsFormsHost
            WindowsFormsHost host = new WindowsFormsHost();
            host.Child = new MonthCalendar();
            
            // Place the WindowsFormsHost in the Expander
            expander.Content = host;
            
            // Add the Expander to the ElementHost
            elementHost.Child = expander;
        }
    }
}