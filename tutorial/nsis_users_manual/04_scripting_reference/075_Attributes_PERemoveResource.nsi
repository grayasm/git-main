; PERemoveResource [/NOERRORS] restype resname reslang | ALL
;
; Removes a resource added with PEAddResource.

PEAddResource "074_attributes_icon.ico" "#Icon" "#200"
PERemoveResource "#Icon" "#200" ALL


Section
SectionEnd