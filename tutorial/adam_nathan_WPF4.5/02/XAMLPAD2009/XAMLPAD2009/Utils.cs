using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Xaml;
using System.Xml;

namespace XAMLPAD2009
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
            using (XamlXmlWriter writer = new XamlXmlWriter(xmlWriter, reader.SchemaContext))
            {
                // Simple node loop
                while (reader.Read())
                {
                    writer.WriteNode(reader);
                }
                return textWriter.ToString();
            }
        }

        // This is Listing 2.3, but enhanced to change relevant Window properties into Page properties
        public static object ConvertXmlStringToMorphedObjectGraph(string xmlString)
        {
            // String -> TextReader -> XamlXmlReader
            using (TextReader textReader = new StringReader(xmlString))
            using (XamlXmlReader reader = new XamlXmlReader(textReader,
            System.Windows.Markup.XamlReader.GetWpfSchemaContext()))
            using (XamlObjectWriter writer = new XamlObjectWriter(reader.SchemaContext))
            {
                int windowDepth = -1; // So we only modify Window properties
                int depth = 0;
                XamlType pageType = new XamlType(typeof(Page), reader.SchemaContext);

                // Node loop
                while (reader.Read())
                {
                    switch (reader.NodeType)
                    {
                        case XamlNodeType.StartObject:
                            depth++;

                            if (reader.Type.UnderlyingType == typeof(Window))
                            {
                                windowDepth = depth;
                                // Turn a Window into a Page
                                writer.WriteStartObject(pageType);
                            }
                            else
                            {
                                // Just write the node as-is
                                writer.WriteNode(reader);
                            }
                            break;

                        case XamlNodeType.EndObject:
                            depth--;
                            if (windowDepth != -1 && depth < windowDepth)
                                windowDepth = -1;

                            // Just write the node as-is
                            writer.WriteNode(reader);
                            break;

                        case XamlNodeType.StartMember:
                            if (depth == windowDepth)
                            {
                                XamlMember newMember = pageType.GetMember(reader.Member.Name);
                                if (newMember != null && !newMember.IsEvent && newMember != XamlLanguage.Class)
                                {
                                    writer.WriteStartMember(newMember);
                                }
                                else
                                {
                                    // This is a Window member that isn't on Page (or it's an event or x:Class), so just skip it.
                                    // reader.Skip();
                                    // Skip seems to be skipping too much, so manually skip the following Value & EndMember instead (assumes simple value!)
                                    reader.Read();
                                    reader.Read();
                                }
                            }
                            // Skip events and x:Class
                            else if (reader.Member.IsEvent || reader.Member == XamlLanguage.Class)
                            {
                                // reader.Skip();
                                // Skip seems to be skipping too much, so manually skip the following Value & EndMember instead (assumes simple value!)
                                reader.Read();
                                reader.Read();
                            }
                            else
                            {
                                // Just write the node as-is
                                writer.WriteNode(reader);
                            }
                            break;

                        default:
                            // Just write the node as-is
                            writer.WriteNode(reader);
                            break;
                    }
                }
                // When XamlObjectWriter is done, this is the root object instance
                return writer.Result;
            }
        }
    }
}