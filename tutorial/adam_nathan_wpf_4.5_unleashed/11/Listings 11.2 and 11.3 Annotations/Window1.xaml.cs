using System;
using System.IO;
using System.Windows;
using System.Windows.Annotations;
using System.Windows.Annotations.Storage;

public partial class Window1 : Window
{
    Stream stream;

    public Window1()
    {
        InitializeComponent();
    }

    protected void OnInitialized(object sender, EventArgs e)
    {
        // Enable and load annotations
        AnnotationService service = AnnotationService.GetService(reader);
        if (service == null)
        {
            stream = new FileStream("storage.xml", FileMode.OpenOrCreate);
            service = new AnnotationService(reader);
            AnnotationStore store = new XmlStreamStore(stream);
            service.Enable(store);
        }
    }

    protected void OnClosed(object sender, EventArgs e)
    {
        // Disable and save annotations
        AnnotationService service = AnnotationService.GetService(reader);
        if (service != null && service.IsEnabled)
        {
            service.Store.Flush();
            service.Disable();
            stream.Close();
        }
    }
}