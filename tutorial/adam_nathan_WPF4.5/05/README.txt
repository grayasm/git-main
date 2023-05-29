==Chapter 5. Layout with Panels==

	The 5 main buil-in panels from System.Windows.Controls
		Canvas
		StackPanel
		WrapPanel
		DockPanel
		Grid

	Canvas
		Is the most basic panel.
		Position elements by coordinates (pixels).
		Position elements relative to any corner. (Canvas.Top, Canvas.Left,..)
		Elemens added later are placed on top of elements added earlier.
		The change the Z order use Canvas.ZIndex="1"

	StackPanel
		Is the most popular.
		It stacks its children.
		One way to customize the StackPanel by Orientation=Horizontal,Vertical
		Vertical default stacking.

	WrapPanel
		Is similar to StackPanel.
		It stacks its children + wraps them to additional rows or columns.
		Customize by Orientation=Horizontal,Vertical
		Horizontal default stacking (like File Exporer's Thumbnails view)
		Any elements taller than ItemHeight get clipped.
		Any elements wider than ItemWidth get clipped.

	DockPanel
		Behaves much like Canvas, but the docked element will fill the entire
		space left. The element is streched to fill the entire width or height.
		DockPanel.Dock=Top,Left,Right,Bottom
		HorizontalAlignment=Left,Right
		VerticalAlignment=Top,Bottom

	Grid
		Stacks the elemens in a multirow and multicolumn fashion.
		GridSplitter allows for interactive resizing of rows and columns.


	Primitive Panels
		All these panels are in the System.Windows.Controls.Primitives
		TabPanel
		ToolBarPanel
		ToolBarOverflowPanel
		ToolBarTray
		UniformGrid
		SelectiveScrollingGrid

	Clipping
		All UIElements have a Boolean ClipToBounds to control whether children
		elements can be rendered outside its bounds. (Either way it looks bad)

	Scrolling
		Wrap an element in a System.Windows.Controls.ScrollViewer control and
		the element instantly becomes scrollable.

	Scaling
		Viewbox (System.Windows.Controls.Viewbox) provides an easy mechanism to 
		scale arbitrary content within a given space.
		Is known as a decorator and can have only one child element.
		It stretches in both dimensions to fill the space given to it.
		It has the property (enumeration) 
		Stretch:
			None			- no scalling
			Fill			- stretched, non-uniform scalled
			UniformGrid		- best fit, uniform scalled
			UniformToFill	- best fit on width, uniform scalled, clipped

