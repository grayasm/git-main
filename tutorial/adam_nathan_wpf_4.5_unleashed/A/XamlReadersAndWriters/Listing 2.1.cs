using System.IO;
using System.Xaml;

namespace XamlReadersAndWriters
{
    partial class Utils
    {
        public static object ConvertXmlStringToObjectGraph(string xmlString)
        {
            // String -> TextReader -> XamlXmlReader
            using (TextReader textReader = new StringReader(xmlString))
            using (XamlXmlReader reader = new XamlXmlReader(textReader, System.Windows.Markup.XamlReader.GetWpfSchemaContext()))
            using (XamlObjectWriter writer = new XamlObjectWriter(reader.SchemaContext))
            {
                // Simple node loop
                while (reader.Read())
                {
                    writer.WriteNode(reader);
                }
                // When XamlObjectWriter is done, this is the root object instance
                return writer.Result;
            }
        }
    }
}