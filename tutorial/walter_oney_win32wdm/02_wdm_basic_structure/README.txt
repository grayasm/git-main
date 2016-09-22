*
*
    Cap. 2 Basic Structure of a WDM Driver.
	
	01_InterfaceEnum - is a simple WIN32 application executable to enumerate devices.
	02_driver - is a simple driver.
				The samclass.dll (provides an icon and a property sheet for device
				drivers in the class Sample, the class used in this book.)



	Registered device interfaces have persistent registry keys below
	HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\DeviceClasses
	
	Registry functions: help interogate interfaces
	https://msdn.microsoft.com/en-us/library/windows/desktop/ms724875(v=vs.85).aspx
	
	Public Device Installation Functions
	https://msdn.microsoft.com/en-us/library/windows/hardware/ff549791(v=vs.85).aspx
	DiInstallDevice
	DiInstallDriver
	DiRollbackDriver
	DiShowUpdateDevice
	DiUninstallDevice
	InstallSelectedDriver
	SetupDiAskForOEMDisk
	SetupDiBuildClassInfoList
	SetupDiBuildClassInfoListEx
	SetupDiBuildDriverInfoList
	SetupDiCallClassInstaller
	SetupDiCancelDriverInfoSearch
	SetupDiChangeState
	SetupDiClassGuidsFromName
	SetupDiClassGuidsFromNameEx
	SetupDiClassNameFromGuid
	SetupDiClassNameFromGuidEx
	SetupDiCreateDeviceInfo
	SetupDiCreateDeviceInfoList
	SetupDiCreateDeviceInfoListEx
	SetupDiCreateDeviceInterface
	SetupDiCreateDeviceInterfaceRegKey
	SetupDiCreateDevRegKey
	SetupDiDeleteDeviceInfo
	SetupDiDeleteDeviceInterfaceData
	SetupDiDeleteDeviceInterfaceRegKey
	SetupDiDeleteDevRegKey
	SetupDiDestroyClassImageList
	SetupDiDestroyDeviceInfoList
	SetupDiDestroyDriverInfoList
	SetupDiDrawMiniIcon
	SetupDiEnumDeviceInfo
	SetupDiEnumDeviceInterfaces
	SetupDiEnumDriverInfo
	SetupDiFinishInstallAction
	SetupDiGetActualModelsSection
	SetupDiGetActualSectionToInstall
	SetupDiGetActualSectionToInstallEx
	SetupDiGetClassBitmapIndex
	SetupDiGetClassDescription
	SetupDiGetClassDescriptionEx
	SetupDiGetClassDevPropertySheets
	SetupDiGetClassDevs
	SetupDiGetClassDevsEx
	SetupDiGetClassImageIndex
	SetupDiGetClassImageList
	SetupDiGetClassImageListEx
	SetupDiGetClassInstallParams
	SetupDiGetClassProperty
	SetupDiGetClassPropertyEx
	SetupDiGetClassPropertyKeys
	SetupDiGetClassPropertyKeysEx
	SetupDiGetClassRegistryProperty
	SetupDiGetCustomDeviceProperty
	SetupDiGetDeviceInfoListClass
	SetupDiGetDeviceInfoListDetail
	SetupDiGetDeviceInstallParams
	SetupDiGetDeviceInstanceId
	SetupDiGetDeviceInterfaceAlias
	SetupDiGetDeviceInterfaceDetail
	SetupDiGetDeviceInterfaceProperty
	SetupDiGetDeviceInterfacePropertyKeys
	SetupDiGetDeviceProperty
	SetupDiGetDevicePropertyKeys
	SetupDiGetDeviceRegistryProperty
	SetupDiGetDriverInfoDetail
	SetupDiGetDriverInstallParams
	SetupDiGetHwProfileFriendlyName
	SetupDiGetHwProfileFriendlyNameEx
	SetupDiGetHwProfileList
	SetupDiGetHwProfileListEx
	SetupDiGetINFClass
	SetupDiGetSelectedDevice
	SetupDiGetSelectedDriver
	SetupDiGetWizardPage
	SetupDiInstallClass
	SetupDiInstallClassEx
	SetupDiInstallDevice
	SetupDiInstallDeviceInterfaces
	SetupDiInstallDriverFiles
	SetupDiLoadClassIcon
	SetupDiLoadDeviceIcon
	SetupDiOpenClassRegKey
	SetupDiOpenClassRegKeyEx
	SetupDiOpenDeviceInfo
	SetupDiOpenDeviceInterface
	SetupDiOpenDeviceInterfaceRegKey
	SetupDiOpenDevRegKey
	SetupDiRegisterCoDeviceInstallers
	SetupDiRegisterDeviceInfo
	SetupDiRemoveDevice
	SetupDiRemoveDeviceInterface
	SetupDiRestartDevices
	SetupDiSelectBestCompatDrv
	SetupDiSelectDevice
	SetupDiSelectOEMDrv
	SetupDiSetClassInstallParams
	SetupDiSetClassProperty
	SetupDiSetClassPropertyEx
	SetupDiSetClassRegistryProperty
	SetupDiSetDeviceInstallParams
	SetupDiSetDeviceInterfaceDefault
	SetupDiSetDeviceInterfaceProperty
	SetupDiSetDeviceProperty
	SetupDiSetDeviceRegistryProperty
	SetupDiSetDriverInstallParams
	SetupDiSetSelectedDevice
	SetupDiSetSelectedDriver
	SetupDiUnremoveDevice
	UpdateDriverForPlugAndPlayDevices
	
	In Windows10 a INF file cannot install an UNSIGNED driver.
	To sign a driver follow the procedure at:
	https://technet.microsoft.com/en-us/library/dd919238(v=ws.10).aspx
	
	Here is a short summary:
	1)	Create (one time) a digital certificate for signing using MakeCert tool from
		c:\Program Files (x86)\Windows Kits\10\bin\x64\makecert.exe
		
		makecert -r -n "CN=ModuleWorks - for test use only"
				 -ss ModuleWorksCertStore
				 -sr LocalMachine
	
	2)	Add the certificate to the Trusted Root Certification Authorities and
		to Trusted Publishers
	
	3)	Sign the device driver package with the certificate (inside INF file
		it is specified the path to .cat catalog file). Use Inf2Cat.exe from
		c:\Program Files (x86)\Windows Kits\10\bin\x86\Inf2Cat.exe		
		
		inf2cat /driver:d:\workdir\path_to_inf_sys_dll_directory /os:10_x64
		start stupidamd64.cat  # catalog is not digitally signed and cannot be verified info
	
	4)	Finally sign the catalog to be able to intall the driver.
		Call SignTool.exe from the Visual Studio Command Prompt.
	
		signtool sign /s ModuleWorksCertStore /n "ModuleWorks - for test use only"
				 /t http://timestamp.verisign.com/scripts/timestamp.dll
				 stupidamd64.cat
				
		start stupidamd64.cat
		
		
		
		
		
		
		
		