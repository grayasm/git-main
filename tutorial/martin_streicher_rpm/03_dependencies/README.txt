*
*
*
    This is the Part3.pdf : Accomodating software dependencies.
                            by Martin Streicher

    Here I use 1 package:
         part3-0.1-1.x86_64.rpm  with the following dependencies:

         Requires:      zlib >= 5.5, man < 2.0
         Provides:      part3
         Conflicts:     gcc > 3.0, gdb = 5
         Obsoletes:     gzip

    The packages has intentionally incorrect versions to see how yum/rpm
    triggers error messages. Below I fix the package and re-run more times.


root@centos:# rpm -ivh part3-0.1-1.el7.x86_64.rpm
error: Failed dependencies:
        man < 2.0 is needed by part3-0.1-1.el7.x86_64
        zlib >= 5.5 is needed by part3-0.1-1.el7.x86_64
        gcc > 3.0 conflicts with part3-0.1-1.el7.x86_64

mihai@centos:$ man --version
man 2.6.3
[mihai@centos: ~]$ yum info zlib
Loaded plugins: fastestmirror, langpacks, priorities
Loading mirror speeds from cached hostfile
 * base: mirror.netcologne.de
 * elrepo: ftp.nluug.nl
 ...
521 packages excluded due to repository priority protections
Installed Packages
Name        : zlib
Arch        : x86_64
Version     : 1.2.7
Release     : 15.el7
Size        : 181 k
Repo        : installed
From repo   : base
Summary     : The compression and decompression library
URL         : http://www.zlib.net/
License     : zlib and Boost
Description : Zlib is a general-purpose, patent-free, lossless data
            : compression library which is used by many different programs.


** change in spec: man > 2.0, zlib > 1.0


root@centos:# rpm -ivh part3-0.1-1.el7.x86_64.rpm
error: Failed dependencies:
        gcc > 3.0 conflicts with part3-0.1-1.el7.x86_64


** change in spec: gcc < 3.0

root@centos:# rpm -ivh part3-0.1-1.el7.x86_64.rpm
error: Failed dependencies:
        gzip is obsoleted by part3-0.1-1.el7.x86_64

** change in spec: gzip < 1.0


root@centos:# rpm -ivh part3-0.1-1.el7.x86_64.rpm
Preparing...                          ################################# [100%]
Updating / installing...
   1:part3-0.1-1.el7                  ################################# [100%]
