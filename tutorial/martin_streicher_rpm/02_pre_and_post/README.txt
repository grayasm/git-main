*
*
*
    This is the Part2.pdf : Upgrading and uninstalling software.
                            by Martin Streicher

    Here we use 2 packages:
         part2-0.1-1.x86_64.rpm and
         part2-1.1-1.x86_64.rpm

    We install the first version, then upgrade it and finally remove it.


root@centos# rpm -Uhv RPMS/x86_64/part2-0.1-1.x86_64.rpm
Preparing...                          ################################# [100%]
spec: part2-0.1 run %pre 1 hook before install
Updating / installing...
   1:part2-0.1-1                      ################################# [100%]
spec: part2-0.1 run %post 1 hook after install


root@centos# rpm -Uvh RPMS/x86_64/part2-0.1-1.x86_64.rpm
Preparing...                          ################################# [100%]
        package part2-0.1-1.x86_64 is already installed


root@centos# rpm -Uvh RPMS/x86_64/part2-1.1-2.x86_64.rpm
Preparing...                          ################################# [100%]
spec: part2-1.1 run %pre 2 hook before upgrade
Updating / installing...
   1:part2-1.1-2                      ################################# [ 50%]
spec: part2-1.1 run %post 2 hook after upgrade
spec: part2-0.1 run %preun 1 hook before upgrade
Cleaning up / removing...
   2:part2-0.1-1                      ################################# [100%]
spec: part2-0.1 run %preun 1 hook after upgrade


root@centos# yum remove part2
Loaded plugins: fastestmirror, langpacks, priorities
Resolving Dependencies
--> Running transaction check
---> Package part2.x86_64 0:1.1-2 will be erased
--> Finished Dependency Resolution

Dependencies Resolved

================================================================================
 Package             Arch     Version              Repository               Size
================================================================================
Removing:
 part2               x86_64   1.1-2                installed                11 k

Transaction Summary
================================================================================
Remove  1 Package

Installed size: 11 k
Is this ok [y/N]: y
Downloading packages:
Running transaction check
Running transaction test
Transaction test succeeded
Running transaction
Warning: RPMDB altered outside of yum.
spec: part2-1.1 run %preun 0 hook before uninstall
  Erasing    : part2-1.1-2.x86_64                                            1/1
spec: part2-1.1 run %preun 0 hook after uninstall
  Verifying  : part2-1.1-2.x86_64                                            1/1 

Removed:
  part2.x86_64 0:1.1-2

Complete!
