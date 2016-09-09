*
*
    Cap. Beginning a Driver Project
	1.2. Windows Driver Model
	
				Applications								EXE application
					|
				(Win32 API call)
					|
				Win32 Subsystem								ReadFile (API)
	User mode		|
	Kernel mode		|
				(System service interface)
					|
				I/O Manager									NtReadFile (KERNEL32.DLL)
					|
				(IRP passed to driver dispatch routine)		I/O Request Packet = IRP
					|
				Device driver								IRP_MJ_READ
					|										(return to user mode caller with
				(HAL call)									 IRP hasn't finished yet)
					|						
				Hardware abstraction layer					READ_PORT_UCHAR (read single byte from I/O port)
					|
				(Platform specific operation)				IN instruction
					|
				Hardware									After finishing I/O operation, the driver 
															completes IRP by calling a kernel-mode service
															routine and it allows the waiting application
															to resume execution.

	1.3. What kind of driver do I need?
	
			Virtual device			Kernel-mode
			drivers(VDD)			drivers
										|
							+-----------|-----------+
							|			|			|
						File system		PnP			Legacy
						drivers			drivers		drivers
										|
									WDM drivers
										|
				+-----------+-----------+-------------------+
				|			|			|					|
				Class		Mini-		Monolithic			Filter
				drivers		drivers		function drivers	drivers

					
		A PnP driver is a kernel-mode driver that understands the Plug and Play protocol of Windows.
		A WDM driver is a PnP driver that additionaly understands power-management protocols.
		Class driver manages a well defined class of devices (reserved by Microsoft).
		Mini driver supplies a vendor specific help to a class driver.
		Monolithic function driver embodies all the functionality needed to support a hardware device.
		Filter driver filters the I/O operations for a particular device to add or modify behavior.
		File system driver implement the standard PC file system model.
		Legacy device driver is a kernel-mode driver that directly controls a hardware device without help
			from other drivers. Drivers of earlier version of Windows (NT?) that are running without a change.
			
		
		WHQL: Windows Hardware Quality Lab (WHQL) to obtain a digital certificate.
		DUNS: Data Universal Numbering System providing equivalent proof of business organization.
		Verisign: to obtain a signature certificate.
		Installer: to install the driver by end-users.
		WMI: Windows Management Instrumentation subsystem provides a language and transport independent pathway
			for various sorts of binary data.
		System event log: part of Windows since the beginnign of NT; driver can send text messages.
		Control Pangel: and other configuration software should be part of the driver install package
			that WHQL digitally signs. Need to be finished at the same time as the driver.
		
		Milestones for driver development:
		
		1. Evaluation fo required driver and selection of programming talent.
		2. Programming specification for hardware complete enough for driver work to begin.
		3. Prototype hardware available for driver testing.
		4. Driver and hardware/firmware working together as originally intended.
		5. Installation (INF) file tested on all operating systems.
		6. Control panels and other ancillary software done.
		7. WMI and event log functionality done and tested.
		8. WHQL self-tests passed and submission made.
		9. Custom installation program  done (not part of WHQL submission).
		10.Ready to burn discs and ship product!






		