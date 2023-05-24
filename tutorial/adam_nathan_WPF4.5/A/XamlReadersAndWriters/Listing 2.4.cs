using System.IO;
using System.Xaml;
using System.Xml;

namespace XamlReadersAndWriters
{
    partial class Utils
    {
        public static string RewriteXaml(string xmlString)
        {
            // String -> TextReader -> XamlXmlReader
            using (TextReader textReader = new StringReader(xmlString))
            using (XamlXmlReader reader = new XamlXmlReader(textReader))
            // TextWriter -> XmlWriter -> XamlXmlWriter
            using (StringWriter textWriter = new StringWriter())
            using (XmlWriter xmlWriter = XmlWriter.Create(textWriter, new XmlWriterSettings { Indent = true, OmitXmlDeclaration = true }))
            using (XamlXmlWriter writer = new XamlXmlWriter(xmlWriter,
            reader.SchemaContext))
            {
                // Simple node loop
                while (reader.Read())
                {
                    writer.WriteNode(reader);
                }
                return textWriter.ToString();
            }
        }
    }
}