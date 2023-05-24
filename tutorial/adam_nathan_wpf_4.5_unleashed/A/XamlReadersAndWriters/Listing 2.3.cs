using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Xaml;

namespace XamlReadersAndWriters
{
    partial class Utils
    {
        // NOTE: For enhancements to respect Window properties that can also apply to Page, see the version of this function
        //       in the XAMLPAD2009 sample.
        public static object ConvertXmlStringToMorphedObjectGraph(string xmlString)
        {
            // String -> TextReader -> XamlXmlReader
            using (TextReader textReader = new StringReader(xmlString))
            using (XamlXmlReader reader = new XamlXmlReader(textReader,
            System.Windows.Markup.XamlReader.GetWpfSchemaContext()))
            using (XamlObjectWriter writer = new XamlObjectWriter(reader.SchemaContext))
            {
                // Node loop
                while (reader.Read())
                {
                    // Skip events and x:Class
                    if (reader.NodeType == XamlNodeType.StartMember &&
                    reader.Member.IsEvent || reader.Member == XamlLanguage.Class)
                    {
                        reader.Skip();
                    }
                    if (reader.NodeType == XamlNodeType.StartObject && reader.Type.UnderlyingType == typeof(Window))
                    {
                        // Turn a Window into a Page
                        writer.WriteStartObject(new XamlType(typeof(Page), reader.SchemaContext));
                    }
                    else
                    {
                        // Otherwise, just write the node as-is
                        writer.WriteNode(reader);
                    }
                }
                // When XamlObjectWriter is done, this is the root object instance
                return writer.Result;
            }
        }
    }
}