# Include local header
!include 01_sample_header_file.nsh

# Include header from NSIS\Include directory
!include Sections.nsh

Section

Messagebox MB_OK|MB_ICONINFORMATION \
"This is a sample that shows how to use line breaks for larger commands in NSIS scripts"

Messagebox MB_OK|MB_ICONINFORMATION \
"If you want to use a double quote in a string then use this $\" to escape the quote"

MessageBox MB_OK|MB_ICONINFORMATION \
`Altenatively quote the string with $\` `

MessageBox MB_OK|MB_ICONINFORMATION \
'or with $\' '

# for more details see: https://nsis.sourceforge.io/Docs/Chapter4.html#fileformat

SectionEnd