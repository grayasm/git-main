==Chapter 4. Sizing, Positioning and Transforming Elements==


	Testing
		Copy the XAML samples into "01_TestGeneric" MainWindow.xaml between <Grid></Grid>

	FrameworkElement
		All FrameworkElements have Height,MinHeight,MaxHeight,Width,MinWidth,MaxWidth, etc.		
		FrameworkElement is the connecting point between WPF framework-level element classes 
		and the WPF core-level set of UIElement presentation services.
		
		The following classes derive from : FrameworkElement
	
			System.Windows.Controls.AccessText
			System.Windows.Controls.AdornedElementPlaceholder
			System.Windows.Controls.ContentPresenter
			System.Windows.Controls.Control
			System.Windows.Controls.Decorator
			System.Windows.Controls.Image
			System.Windows.Controls.InkCanvas
			System.Windows.Controls.ItemsPresenter
			System.Windows.Controls.MediaElement
			System.Windows.Controls.Page
			System.Windows.Controls.Panel
			System.Windows.Controls.Primitives.DocumentPageView
			System.Windows.Controls.Primitives.GridViewRowPresenterBase
			System.Windows.Controls.Primitives.Popup
			System.Windows.Controls.Primitives.TickBar
			System.Windows.Controls.Primitives.Track
			System.Windows.Controls.TextBlock
			System.Windows.Controls.ToolBarTray
			System.Windows.Controls.Viewport3D
			System.Windows.Documents.Adorner
			System.Windows.Documents.AdornerLayer
			System.Windows.Documents.DocumentReference
			System.Windows.Documents.FixedPage
			System.Windows.Documents.Glyphs
			System.Windows.Documents.PageContent
			System.Windows.Interop.HwndHost
			System.Windows.Shapes.Shape

	Padding and Margin
		myLabel.Margin = new Thickness(10);  		equivalent to
		<Label Margin="10"
		
		myLabel.Margin = new Thickness(20,5,20,5);	equivalent to
		<Label Margin="20,5"

	WPF unit of measure
		All measurements such as Margin="20,5" are specified in 
		device-independent pixels. These "logical pixels" are 1/96 inch,
		regardless of the screen DPI setting. These are always specified as
		double values, so they can be fractional.

	Visibility
		Visibility is defined on UIElement.
		Has 3 states: Visible,Collapsed,Hidden.
		<Button Visibility="Collapsed">Collapsed Button</Button>

	Controlling Position
		Alignment (from System.Windows.)
			HorizontalAlignment=Left,Center,Right,Stretch
			VerticalAlignment=Top,Center,Bottom,Stretch

			HorizontalContentAlignment, VerticalContentAlignment
			<Button HorizontalContentAlignment="Stretch" Background="Lime">Stretch</Button>

	FlowDirection
		System.Windows.FlowDirection=LeftToRight,RightToLeft
		Coresponds to the curent culture language that is read from R to L, or L to R.

	Applying Transforms
		System.Windows.Media.Transform is the base class.
		FrameworkElements has 2 properties of type Transform
			LayoutTransform  (moves objects out of the way, rearranges the layout)
			RenderTransform  (objects overlap)
		
		RotateTransform
		ScaleTransform
		SkewTransform
		MatrixTransform