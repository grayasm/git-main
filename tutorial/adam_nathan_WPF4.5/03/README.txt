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
		Example "01_DependencyProperty" compiles the code from "Listing 3.3 Standard Dependency Property.cs.txt"
		
		Say you want a Button to change its color when the mouse hovers over it:
			Without property triggers:
			
			<Button MouseEnter="Button_MouseEnter" MouseLeave="Button_MouseLeave"
					MinWidth="75" Margin="10">Help</Button>
		
			void Button_MouseEnter(object sender, MouseEventArgs e)
			{
				Button b = sender as Button;
				if (b != null) b.Foreground = Brushes.Blue;
			}

			With a property trigger:
			
			<Trigger Property="IsMouseOver" Value="True">
				<Setter Property="Foreground" Value="Blue"/>
			</Trigger>


	Support for Multiple Providers
		WPF follows a well defined mechanism to calculate a property final value.
		
		(1)	             (2)                   (3)           (4)        (5)
		Determine   ->   Evaluate           -> Apply      -> Coerce  -> Validate
		Base Value      (if an Expression)     Animations
		
		(1) Base Value's 10 Providers in order from highest to lowest precedence:
		1. Local value
		2. Parent template trigger
		3. Parent template
		4. Style triggers
		5. Template triggers
		6. Style setters
		7. Theme style triggers
		8. Theme style setters
		9. Property value inheritance
		10. Default value

	Attached Properties
		Setting FontSize for the StackPanel element doesn't work because StackPanel
		doesn't have any font-related properties of its own. Instead you must use
		the FontSize attached property on class TextElement.
		
		<StackPanel FontSize="30" 				--Not OK
		<StackPanel TextElement.FontSize="30" 	--OK

