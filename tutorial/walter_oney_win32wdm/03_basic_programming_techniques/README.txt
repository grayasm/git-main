*
*
	Capter. 3 Basic Programming Techniques.
	
	01_generic: contains function called from some other SYS drivers in cap3.
	07_fputest: is 32bit only due to use of MMX and __asm extension.

	
	Kernel-Mode Driver Reference from MSDN:
	https://msdn.microsoft.com/en-us/library/windows/hardware/ff547794(v=vs.85).aspx
	
	
		1.1) Standard Driver Routines
		1.2) Driver Support Routines
		1.3) Kernel Data Types
		1.4) Silo DDI reference
		
		1.1) Standard Driver Routines
			DriverEntry, AddDevice, DispatchXxx (beginning with Dispatch), Unload.
			Other routines are optional depending where the driver is in the device stack.
			
		1.2) Driver Support Routines
			Initialization and Unload
				Hardware Configuration
				Registry
				Objects and Resources
				Initializing Driver-Managed Queues
			IRPs
				Processing IRPs
				Driver-Allocated IRPs
				File Objects
			Synchronization
				Driver Routines and I/O Objects
				IRQL
				Spin Locks and Interlocks
				Timers
				Driver Threads, Dispatcher Objects and Resources
			Memory Allocation and Buffer Management
				Buffer Management
				Long-Term Internal Driver Buffers
				Buffered Data and Buffer Initialization
				Address Mappings and MDLs
				Buffer and MDL Management
				Device Memory Access
				Pageable Drivers
				Sections and Views
				Access to Structures
			Plug and Play Routines
				Device Information Routines
				Registry Routines
				Device Interface Routines
				PnP Notification Routines
				Remove Lock Routines
				Other PnP Routines
			Window Management Instrumentation Routines
				WMI IRP Processing Routines
				WMI IRP Sending Routines
			DMA
			PIO
			Interrupts
			Driver-Managed Queues
			Driver System Threads
			Strings
			Data Conversions
			Access to Driver-Managed Objects
			Error Handling
			
		1.3) Kernel Data Types
			System-Defined Integer Data Types
			System-Defined Enumerations and Constants
			System-Defined Data Structures
			System-Supplied Driver Interfaces
			IRP Function Codes
				System-Defined I/O Function Codes
					IRP Major Function Codes
					Plug and Play Minor IRPs
					Power Management Minor IRPs
					WMI Minor IRPs
		
		1.4) Silo DDI Reference
			These DDIs offer that ability for kernel components to learn about the server silos that are
			created and destroyed on a machine.
			
			Context Management
			Threading
			Monitoring
			Helpers
			
	Overview of the Kernel-Mode support routines
	--------------------------------------------
		2.1.	The I/O Manager (prefix Io)
		2.2.	The Process Structure module (prefix Ps) - for kernel-mode threads
		2.3.	The Memory Manager (prefix Mm) - page tables.
		2.4.	The executive (prefix Ex) - for heap management and synchronization.
		2.5.	The Object Manager (prefix Ob) - access to many Windows data objects.
		2.6.	The Security Reference Monitor (prefix Se) - security checks on files.
		2.7.	The Runtime Library Component (prefix Rtl) - utility routines (e.g. strings)
		2.8.	The Kernel-Mode Callers (prefix Zw)
		2.9.	The Windows Kernel (prefix Ke) - low-level threads/processes synchronization.
		2.10.	The Hardware Abstraction (prefix Hal) - interrupts,I/O and memory mapped devices, etc.
		
		
			
			
			
			
			
			
			
			
			
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	