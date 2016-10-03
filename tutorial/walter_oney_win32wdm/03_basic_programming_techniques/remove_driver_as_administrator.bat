@rem		To remove driver "stupid.sys" here is what to do:

@rem	1)	Search in C:/Windows/System32/DriverStore for stupid.sys
@rem		The driver will be in a folder with a name like this: stupid.inf_amd64_29a15e866e5ee754

@rem    2)	Search in the registry for the last token "29a15e866e5ee754"
@rem		The taken will be found inside a key like "oem28.inf"

@rem    3)	As administrator run in cmd.exe:   pnputil.exe /delete-driver oem28.inf
