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

GtkAboutDialog
GtkFileChooserDialog
GtkFontSelectionDialog
GtkColorSelectionDialog


-----------
hierarchy:
hold:
ctor:
api:
behavior:
