#include "Window1.h"

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Media;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application^ application = gcnew Application();
	Window^ window = gcnew Window1();
	window->Title = "Hosting Win32 DirectShow Content in WPF";
	window->Background = Brushes::Orange;
	application->Run(window);
	return 0;
}
