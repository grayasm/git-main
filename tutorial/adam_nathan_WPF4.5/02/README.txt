==Chapter 2. XAML Demystified==

	Build XAMLPAD2009.sln & run the program XAMLPAD2009
		Copy the content of each xaml file ("01 Figure 2.1.xaml", ...)
		into the lower window, and watch the upper window changing.


	Load MixingXamlWithProceduralCode.sln
		The content of all xaml files ("01 Figure 2.1.xaml", ...) has already
		been copied into MyWindow.xaml inside the <Grid></Grid> as comments.
		Uncomment each code snippet, build and watch the change to the program.


	Specifications for XAML and XAML Vocabularies

		Google "WPF XAML specifications" as given links are 404
		Some links are:
		https://learn.microsoft.com/en-us/dotnet/desktop/wpf/advanced/xaml-syntax-in-detail?view=netframeworkdesktop-4.8
		https://www.w3.org/TR/REC-xml-names/

	Namespaces
		The mapping of WPF namespaces is hard-coded inside WPF assemblies.
		The root object element in a XAML file must specify at least one XML namespace.
		Additional XML namespaces can be declared on root or on children,
		but each must be given a distinct prefix.

		xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
			is the primary namespace and maps all the following .NET namespaces
		
			System.Windows
			System.Windows.Automation
			System.Windows.Controls
			System.Windows.Controls.Primitives
			System.Windows.Data
			System.Windows.Documents
			System.Windows.Forms.Integration
			System.Windows.Ink
			System.Windows.Input
			System.Windows.Media
			System.Windows.Media.Animation
			System.Windows.Media.Effects
			System.Windows.Media.Imaging
			System.Windows.Media.Media3D
			System.Windows.Media.TextFormatting
			System.Windows.Navigation
			System.Windows.Shapes
			System.Windows.Shell
		
		xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml" is
			the secondary namespace, defines some special compiler/parser
			directives and maps to types in the
			
			System.Windows.Markup
		
		WPF 3.0 shipped with support for:
		http://schemas.microsoft.com/winfx/2006/xaml/presentation
		
		WPF 3.5 defined a new XML namespace:
		http://schemas.microsoft.com/netfx/2007/xaml/presentation
		
		WPF 4.0 defined a new XML namespace 
		http://schemas.microsoft.com/netfx/2009/xaml/presentation

		WPF 4.5 did not add a new XML namespace.


		The winfx/2006 namespace means version 3.0 or later.
		The netfx/2007 namespace means version 3.5 or later.
		The netfx/2009 namespace means version 4.0 or later.
		
	TypeConverter
		See "13_TypeConverter" for using TypeConverter in procedural code.
		XAML find the appropriate type converter by looking at the
		System.ComponentModel.TypeConverterAttribute on the property definition
		See bellow Brush custom attribute

		namespace System.Windows.Media
		{
			//
			// Summary:
			//     Defines objects used to paint graphical objects. 
			//     Classes that derive from System.Windows.Media.Brush
			//     describe how the area is painted.
			[Localizability(LocalizationCategory.None, Readability = Readability.Unreadable)]
			[TypeConverter(typeof(BrushConverter))]
			[ValueSerializer(typeof(BrushValueSerializer))]
			public abstract class Brush : Animatable, IFormattable, IResource
			{...}
		}
	
	Markup Extensions
		See 14_MarkupExtension MainWindow.xaml for the examplanation on
		mapping the XAML items to WPF classes as for ex:
		Background="{x:Null}" 
		x:Null maps to System.Windows.Markup.NullExtension

