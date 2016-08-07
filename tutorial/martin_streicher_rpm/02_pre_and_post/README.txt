*
*
*
    This is the Part2.pdf : Upgrading and uninstalling software.
                            by Martin Streicher

    Here we use 2 packages:
         part2-0.1-1.x86_64.rpm and
         part2-1.1-1.x86_64.rpm

    We install the first version, then upgrade it and finally remove it.


root@centos:# rpm -Uvh RPMS/x86_64/part2-0.1-1.x86_64.rpm
Preparing...                          ################################# [100%]
spec: part2-0.1 run %pre 1 hook before install
Updating / installing...
   1:part2-0.1-1                      ################################# [100%]
spec: part2-0.1 run %post 1 hook after install


root@centos:# rpm -Uvh RPMS/x86_64/part2-0.1-1.x86_64.rpm
Preparing...                          ################################# [100%]
        package part2-0.1-1.x86_64 is already installed


root@centos:# rpm -Uvh RPMS/x86_64/part2-1.1-2.x86_64.rpm
Preparing...                          ################################# [100%]
spec: part2-1.1 run %pre 2 hook before upgrade
Updating / installing...
   1:part2-1.1-2                      ################################# [ 50%]
spec: part2-1.1 run %post 2 hook after upgrade
spec: part2-0.1 run %preun 1 hook before upgrade
Cleaning up / removing...
   2:part2-0.1-1                      ################################# [100%]
spec: part2-0.1 run %preun 1 hook after upgrade


root@centos:# rpm -e part2
spec: part2-1.1 run %preun 0 hook before uninstall
spec: part2-1.1 run %preun 0 hook after uninstall
removed directory: ‘/tmp/part2/bin’
removed directory: ‘/tmp/part2/etc’
removed directory: ‘/tmp/part2’
root@centos:# ll /tmp/part2
ls: cannot access /tmp/part2: No such file or directory
