*
*
	3.3.1 User-Mode and Kernel-Mode Address Spaces
	
	The whole point of a virtual memory system is that you can have a virtual 
	address space that’s much bigger than the amount of physical memory on the 
	computer. To accomplish this feat, the Memory Manager needs to swap page 
	frames in and out of physical memory. Certain parts of the operating system 
	can’t be paged, though, because they’re needed to support the Memory
	Manager itself. The category of “must be resident” stuff is much broader than 
	just the page fault handlers. Windows allows hardware interrupts to occur at 
	nearly any time, including while a page fault is being serviced.
	
	Every hardware interrupt service routine must be in nonpaged memory.
	Code executing at or above interrupt request level (IRQL) DISPATCH_LEVEL 
	cannot cause page faults.
	
	You can use the PAGED_CODE preprocessor macro (declared in wdm.h) to help 
	you discover violations of this rule in the checked build of your driver.
	