==Cap. 6 Input Events: Keyboard, Mouse, Stylus and Touch==

	Two pieces of important plumbing in WPF - routed events and commands.
	
	Routed Events
		Tunneling - the event travels from the root down the tree until the
					source element is reached, or until the event is handled.
		Bubbling  - the event travels from the source element up the tree until
					the root is reached, or until the event is handled.
		Direct    - the event is raised only on the source element.

	Attached Events
		WPF supports tunneling and bubbling of routed events through elements
		that don't even define that event.
		Attached events operate pretty much like attached properties.

	Keyboard Events
		Key,ImeProcessedKey,DeadCharProcessedKey and SystemKey - a large
		enumeration of every possible key.
		IsUp,IsDown and IsToggle - boolean properties of key event.
		KeyStates - bit flag enumeration as: None,Down or Toggled.
		IsRepeat - a boolean that is true when the key is being repeated.
		KeyboardDevice - asking what keys are down or requesting focus to be
			moved to a specific element.

	Mouse Events
		All UIElements support the following basic mouse events:
			MouseEnter, MouseLeave
			MouseMove, PreviewMouseMove
			MouseLeftButtonDown, MouseRightButtonDown, MouseLeftButtonUp,
			MouseRightButtonUp, MouseDown and MouseUp
			PreviewXXX versions of all six of the events above.
			MouseWheeel, PreviewMouseWheel
			DragEnter, DragOver, DragLeave
			PreviewDragEnter, PreviewDragOver and PreviewDragLeave
			Drop and PreviewDrop
			QueryContinueDrag and PreviewQueryContinueDrag
		
		Use GetPosition of MouseEventArgs.
		Data a property of type IDataObject that represents the Win32 clipboard
		object being dragged or dropped.
		Effects and AllowedEffects - bit flags
		KeyStates - another bit flag enumeration that reveals which of the
			following are pressed during the drag and drop:
			LeftMouseButton, RightMouseButton, MiddleMouseButton,
			ShiftKey, ControlKey, AltKey and None.
		
		Capturing the Mouse
			WPF enables any UIElement to capture and release the mouse at any
			time, even if the mouse pointer is not within its bounds with:
			CaptureMouse and ReleaseMouseCapture.
			Other methods:
			IsMouseCaptured, IsMouseCaptureWithin
			GotMouseCapture, LostMouseCapture,
			IsMouseCaptureChanged, IsMouseCaptureWithinChanged.

	Stylus Events
		3 ways to get an instance of a System.Windows.Input.StylusDevice
			MouseEventsArgs property StylusDevice
			CurrentStylusDevice property of System.Windows.Input.Stylus
			Handle a number of events specific to the stylus.
			
		StylusDevice contains a number of properties:
			Inverted 	- Boolean, if it is used as an eraser or not.
			InAir 		- Boolean, if it is in contact with screen.
			StylusButtons- each StylusButton has a string Name and a Guid identifier
						along with a SylusButtonState: Up or Down
			TabletDevice - provides detailed information about the current
						hardware and capabilities (pressure-sensitivity or
						in-air movement).
			X	- the X relative to passed-in element (horizontal)
			Y	- the Y relative to passed-in element (vertical)
			PressureFactor - value between 0 and 1

		Stylus specific events
			StylusEnter, StylusLeave
			StylusMove, PreviewStylusMove
			StylusInAirMove, PreviewStylusInAirMove
			StylusDown, StylusUp, PreviewStylusDown, PreviewStylusUp
			StylusButtonDown, StylusButtonUp
			PreviewStylusButtonDown, PreviewStylusButtonUp
			StylusSystemGesture, PreviewStylusSystemGesture
			StylusInRange, StylusOutOfRange
			PreviewStylusInRange, PreviewStylusOutOfRange
			GotStylusCapture, LostStylusCapture
	
	Touch Events
		TouchEnter, TouchLeave
		TouchMove, PreviewTouchMove
		TouchDown, TouchUp, PreviewTouchDown, PreviewTouchUp
		GotTouchCapture, LostTouchCapture
		
		GetTouchPoint - gets the point relative to passed-in element.
		GetIntermediateTouchPoints - similar with GetStylusPoints
		TouchDevice - returns an instance of TouchDevice.