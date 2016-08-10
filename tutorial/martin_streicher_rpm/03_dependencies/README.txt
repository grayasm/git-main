*
*
*
    This is the Part3.pdf : Accomodating software dependencies.
                            by Martin Streicher

    Here I use 1 package:
         part3-0.1-1.x86_64.rpm  with the following dependencies:

         Requires:
         Provides:
         Conflicts:
         Obsoletes:

    The packages has intentionally incorrect versions to see how yum/rpm
    triggers error messages. Below I fix the package and re-run more times.


root@centos:# rpm -ivh part3-0.1-1.el7.x86_64.rpm
error: Failed dependencies:
        zlib >= 5.5 is needed by part3-0.1-1.el7.x86_64

