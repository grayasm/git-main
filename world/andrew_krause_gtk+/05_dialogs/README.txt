Chapter 5 - Dialogs


GtkDialog:
-----------
hierarchy: ->GtkWidget->GtkBin->GtkWindow->GtkDialog
hold: the dialog contains a GtkVBox, a GtkHButtonBox and a separator member.
ctor: gtk_dialog_new
api: gtkdialog.h
behavior: modal dialogs are created with GTK_DIALOG_MODAL, and
          nonmodal dialogs are created with GTK_DIALOG_DESTROY_WITH_PARENT


GtkMessageDialog:
-----------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkWindow->GtkDialog->GtkMessageDialog
hold: a dialog with some message text.
ctor: gtk_message_dialog_new
api: gtkmessagedialog.h
behavior:

GtkAboutDialog:
---------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkWindow->GtkDialog->GtkAboutDialog
hold: packs multiple widgets to show info about a program (logo,name,website,etc)
ctor: gtk_about_dialog_new
api: gtkaboutdialog.h
behavior: displays information about an application like name, copyright,
          current version, license content, authors, documenters, artists and
          translators. Every property is optional.


GdkPixbuf:
----------
hierarchy: GObject->GdkPixbuf
hold: an image in memory
ctor: gdk_pixbuf_new
api: /usr/include/gdk-pixbuf-2.0/gdk-pixbuf/gdk-pixbuf-core.h
behavior: it contains information about an image stored in memory. It allows
          you to build images manually b placing shapes or pixels or to load
          a prebuilt image from a file. It is derived directly from GObject.

GtkFileChooserDialog:
---------------------
hierarchy: ->GtkWidget->GtkContainer->GtkBin->GtkWindow->GtkDialog->
                                                            GtkFileChooserDialog
hold: is a dialog box suitable for use with "File/Open" or "File/Save as" cmds.
ctor: gtk_file_chooser_dialog_new
api: gtkfilechooserdialog.h
behavior: it is simply a dialog that uses a GtkFileChooserWidget
          (see gtkfilechooserwidget.h) as its child. Since it implements the
          GtkFileChooser interface, you do not ever have to directly access its
          child widget.
          GtkFileChooserWidget is the actual widget that allows the user to
          choose a file or folder. It can also facilitate the creation of a
          folder or saving of a file. When you use a GktFileChooserDialog,
          you are actually using a file chooser widget packed into a GtkDialog.



GtkFontSelectionDialog
GtkColorSelectionDialog


-----------
hierarchy:
hold:
ctor:
api:
behavior:
