Chapter 10 - Dynamic User Interfaces

For Glade program check official page:
http://developer.gnome.org/glade/stable/getting-started.html.en

Glade can be configured to save in 2 formats: libglade or GtkBuilder.
Samples in this chapter uses libglade (GladeXML)


GladeXML:
----------
hierarchy: GObject->GladeXML
hold: and 'instantiation' of an XML interface after an XML file is read.
ctor: glade_xml_new
api:  /usr/include/libglade-2.0/glade/glade-xml.h
behavior: it represents an instantiation of an XML interface description.
          When one of these objects is created, the XML file is read, and
          the interface is created. The GladeXML object then provides an
          interface for accessing the widgets in the interface by the names
          assigned to them inside the XML description.
          The GladeXML object can also be used to connect handlers to the
          named signals in the description. Libglade also provides an interface
          by which it can look up the signal hanlder names in the program's
          symbol table and automatically connect as many handlers up as it can
          that way.

Glade Interface Designer Manual:
https://developer.gnome.org/glade/stable/getting-started.html.en
https://www.youtube.com/results?q=glade+interface+designer


          Connecting a signal in .cpp to a handler:
          glade_xml_signal_connect (xml, "handler name whatever", CALLBACK)

          Connecting a signal in .cpp to a handler and passing some data:
          glade_xml_signal_connect_data (xml, "hanlder", CALLBACK, (gpointer)data)
