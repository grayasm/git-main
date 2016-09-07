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

