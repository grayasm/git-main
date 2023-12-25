#!/bin/bash
#
# SCRIPT: NAME_of_SCRIPT
# AUTHOR: AUTHORS_NAME
# DATE:   DATE_of_CREATION
# REV:    1.1.A (Valid are A, B, D, T, and P)
#               (For Alpha, Beta, Dev, Test and Production)
#
# PLATFORM: (SPECIFY: AIX, HP-UX, Linux, OpenBSD, Solaris
#                     or Not platform dependent)
#
# PURPOSE: Give a clear, and if necessary, long description of the
#          purpose of the shell script. This will also help you stay
#          focused on the task at hand.
#
# REV LIST:
#        DATE: DATE_of_REVISION
#        BY:   AUTHOR_of_MODIFICATION
#        MODIFICATION: Describe what was modified, new features, etc--
#
# set -n   # Uncomment to check script syntax, whithout execution.
#          # NOTE: Do not forget to put the comment back in or
#          #       the shell script will not execute!
# set -x   # Uncomment to debug this shell script
#
##########################################################
#        DEFINE FILES AND VARIABLES HERE
##########################################################

OF=/temp/my-backup-$(date +%Y%m%d).tgz

STR="Hello World!"

##########################################################
#        DEFINE FUNCTIONS HERE
##########################################################

f()
{
    echo "OF=$OF"
    echo "STR=$STR"
}

##########################################################
#        BEGINNING OF MAIN
##########################################################

main()
{
    f
}

main
# End of script
