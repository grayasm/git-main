# A NSIS script contains:
#   Installer Attributes
#   Pages
#   Sections/Functions
#   Compiler Commands
#   The OutFile instruction



### Installer Attributes determine the behaviour and the look and feel.
# see: https://nsis.sourceforge.io/Docs/Chapter4.html#instattribs
Name "Application Installer v.1.0"
InstallDir "$PROGRAMFILES64\Application-1.0"
BrandingText /TRIMRIGHT "Application Installer version 1.0"


### Pages (a set of wizard pages for the user)
# A typical set of pages looks like this:
Page license
Page components
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles


### Sections
# see: https://nsis.sourceforge.io/Docs/Chapter4.html#sections
# Each section coresponds to one component on the components page.
# The section's name is the displayed component name and the section code will
#       be executed if that component is selected.
# It is possible to build your installer with only one section but if you want
#       to use the components page and let the user choose what to install,
#       you'll have to use more than one section.
# Uinstallers can also have multiple sections. Uninstaller section names are
#       prefixed with 'un.'

Section "Installer Section"
SectionEnd

Section "un.Uninstaller Section"
SectionEnd

Section "My Application"
    # The most basic instructions are SetOutPath which tells the installer
    # where to extract the files and File which extracts files.
    SetOutPath $INSTDIR
    File "README.txt"
SectionEnd


### Functions
# see: https://nsis.sourceforge.io/Docs/Chapter4.html#functions
# Functions can contain script code just like sections.
# There are 2 types of functions: User Functions and Callback Functions.
# User Functions:
# --------------
#   * are called by the user from within sections or other functions
#       using the Call instruction
#   * will not execute unless you call them. After the code in the function has
#       executed the installer will continue executing the instructions that
#       came after the Call instruction, unless you have aborted the installation
#       inside the function.
#   * are very useful if you have a set of instructions that need to be executed
#       at serveral locations in the installers. It saves the copying time.
# Callback Functions:
# ------------------
#   * are called by the installer upon certain defined events such as when
#       the installer starts.
#   * are optional. The NSIS compiler will recognize (e.g. onInit) it as a
#       callback function by the name and will call it when the installer starts.

Function .onInit
    MessageBox MB_YESNO "This will install My Application. Do you wish to continue?" IDYES gogogo
        Abort
    gogogo:
FunctionEnd

#   * Abort has a special meaning in callback functions.
#   see: https://nsis.sourceforge.io/Docs/Chapter4.html#callbacks









