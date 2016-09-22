@rem Note:	replace.exe does not support regular expressions 
@rem		we assume "EnableFastChecks" is the default
@rem
@rem		Copy the executable together with this bat file.

replace.exe -find "<BasicRuntimeChecks>EnableFastChecks</BasicRuntimeChecks>" -replace "<BasicRuntimeChecks>Default</BasicRuntimeChecks>"  -fname *.vcxproj
