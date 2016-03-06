Chapter 8 - The TREE VIEW Widget


GtkScrolledWindow: see README.txt for cap.7
-----------------

GtkTreeView: https://developer.gnome.org/gtk2/stable/GtkTreeView.html
------------
hierarchy: ->GtkWidget->GtkContainer->GtkTreeView
hold: any object that implements the GtkTreeModel interface
ctor: gtk_tree_view_new
api:  gtkttreeview.h
behavior: the concept - https://developer.gnome.org/gtk2/stable/TreeWidget.html
          To create a tree or list in GTK+ use GtkTreeModel interface in
          conjunction with the GtkTreeView widget, which is designed around
          a Model/View/Controller design and consists of four major parts:
          1) The tree view widget GtkTreeView
          2) The view column      GtkTreeViewColumn
          3) The cell renderers   GtkCellRenderer,GtkCellRenderer{Text,Pixbuf,Toggle}
          4) The model interface  GtkTreeModel

          The View is composed of the first 3 objects, while the last is
          the Model. One of the prime benefits of the MVC design is that
          multiple views can be created of a single model (e.g view icons,
          list, compact, detailed, thumbnails,etc).
          The purpose of the cell renderers is to provide extensibility to the
          widget and to allow multiple ways of rendering the same type
          of data (e.g. gboolean rendered as "True"-"False", "On"-"Off" or as
          a checkbox).


--------------------------------------------------------------------------------
MVC (google Model/View/Controller pattern) works like this:
1) Controller -gets input from GUI/Keyboard/Mouse/etc
              -changes the Model
              -updates the View
2) View       -displays an interpretation of the Model (pie,bars,etc)
3) Model      -contains data (std::string,std::vector,etc)

* Loki Astari: says that any new View should be registered as an observer on the
  Model. When the Model is updated (by a control) the View is notified and will
  change its appearance to reflect the change in the Model.
* Me: however if a Model is changed in a sequence of actions and only at the end
  a View update is needed this gets complicated. If a large Model takes
  considerable time to be updated in a View then it must be a logic put
  somewhere to buffer the changes on the Model.
  Now makes sense to keep the Controller in place for such things.
--------------------------------------------------------------------------------


GtkListStore:
------------
hierarchy: GObject->GtkListStore
hold: is a list model for use with a GtkTreeView widget.
ctor: gtk_list_store_new
api:  gtkliststore.h
behavior: implements GtkTreeModel interface and all methods. It implements also
          GtkTreeSortable interface so it can be sorted by the view. Finally
          it implements also the tree drag and drop interfaces.
          It can accept most GObject types as a column type, though it can't
          accept all custom types. Internally it will keep a copy of data
          passed in (such as a string or a boxed pointer).


GtkTreeStore:
------------
hierarchy: GObject->GtkTreeStore
hold: is a tree model for use with a GtkTreeView widget.
ctor: gtk_tree_store_new
api:  gtktreestore.h
behavior: implements GtkTreeModel interface and all methods. It implements also
          GtkTreeSortable interface so it can be sorted by the view. Finally
          it implements also the tree drag and drop interfaces.
          It allows to specify the model columns with a <columns> element
          that may contain multiple <column> elements, each specifying one
          model column. The "type" attribute specifies the data type for the
          column.


GtkTreeIter:
------------
hierarchy: GBoxed->GtkTreeIter
hold: a reference to a specific node on a specific Model.
ctor: gtk_tree_model_get_iter
      gtk_tree_model_get_iter_first
api:  gtktreemodel.h
behavior: It is a generic struct with an integer and 3 generic pointers. These
          are filled in by the Model in a model-specific way. The Model defines
          a set of operations using them for navigating the Model. The iterators
          are expected to be always valid for as long as the model is unchanged
          (and doesn't emit a signal).


GtkTreePath:
------------
hierarchy: GBoxed->GtkTreePath
hold: a reference to a specific row on a specific Model
ctor: gtk_tree_model_get_path
api:  gtktreemodel.h
behavior: Songs:0
            mp3s 0:0
            oggs 0:1
          Videos:1
            clips 1:0
              funny clips 1:0:0
              movie trail 1:0:1
            movie 1:1

            A tree path of "3:9:4:1" would basically mean for GTK+:
            go to the 4th top-level row then
               go to the 10th child of that row then
                  go to the 5th child of the previous row and inside that
                     continue to the 2nd child.
