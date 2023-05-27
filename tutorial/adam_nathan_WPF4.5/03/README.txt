==Chapter 3. WPF Fundamentals==

	Compiling and running samples
		Copy/Paste each individual XAML text of the samples:
			"Button with Inline Property Trigger.xaml"
			"Figure 3.8 Built-In Command Bindings.xaml"
			"Listing 3.1 About Dialog.xaml"
			"Listing 3.4 About Dialog - Font Properties on Root.xaml"
			"Listing 3.5 About Dialog - Font Properties Moved.xaml"
		into Window1.xaml of the "Listing 3.2 About Dialog with Tree Walking.sln"


	The core classes that form the foundation of WPF
	
								+------+
								|Object|
								+------+
									|
							+----------------+
							|DispatcherObject|
							+----------------+
									|
							+----------------+
							|DependencyObject|
							+----------------+
									|
		+-------------+---------------------+-----------------------+
		|			  |						|						|
	+---------+    +------+            +--------+					|
	|Freezable|    |Visual|            |Visual3D|					|
	+---------+    +------+            +--------+					|
					  |						|						|
				   +---------+         +-----------+        +--------------+
				   |UIElement|         |UIElement3D|        |ContentElement|
				   +---------+         +-----------+        +--------------+
					  |												|
				   +----------------+                       +-----------------------+
				   |FrameworkElement|                       |FrameworkContentElement|
				   +----------------+                       +-----------------------+
					  |
				   +-------+
				   |Control|
				   +-------+
				   
				   
		Object: 			the base class of all .NET classes
		DispatcherObject: 	base class of any object thread-unsafe
		DependencyObject: 	base class of any object that supports dependency
		Freezable: 			base class of any frozen-able object shareable among threads
		Visual: 			base class of all objects that have their own 2D visual representation
		UIElement: 			base class of all 2D visual objects with support for
							routed events,command binding, layout and focus.
		FrameworkElement: 	the base class that add support for
							styles, data binding, resources and a few common mechanisms
							for controls, such as tooltips and context menus.
		Control: 			the base class for familiar controls such as
							Buttons, ListBox, StatusBar, etc.
		Visual3D: 			the base class for all objects that have their own 3D visual representation.
		UIElement3D: 		the base class for all 3D visual objects with suppor for
							routed events, command binding, and focus.
		ContentElement: 	a base class similar to UIElement but for document-related
							pieces of content that don't have rendering behaviour of their won.
		FrameworkContentElement: the analog to FrameworkElement for content.

	
	
	Logical and Visual Trees
		In WPF, user interfaces are constructed from a tree of objects known
		as a logical tree.
		Every aspect of WPF (properties, events, resources and so on) has
		behavior tied to the logical tree.

	Dependency Properties
		WPF introduces a type of property called a "dependency property"
		Enables styling, automatic data binding, animation and more.
		It depends on providers to determine its value.
		It has built-in ability to provide change notifications.
		See "01_DependencyProperty"