#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 240, The os Module
#           The os module is an umbrella module that presents a reasonably
#           uniform cross-platform view of the different capabilities of
#           various operating systems. The module provides ways to create and
#           handle files and directories, and to create, manage, and destroy
#           processes. This section covers the filesystem-related capabilities
#           of the os module; “Running Other Programs with the os Module” on
#           page 354 covers the process-related capabilities.
#           The os module supplies a name attribute, which is a string that
#           identifies the kind of platform on which Python is being run.
#           Common values for name are 'posix' (all kinds of Unix-like
#           platforms, including Mac OS X), 'nt' (all kinds of 32-bit Windows
#           platforms), 'mac' (old Mac systems), and 'java' (Jython). You can
#           often exploit unique capabilities of a platform, at least in part,
#           through functions supplied by os . However, this book deals with
#           cross-platform programming, not with platform-specific
#           functionality, so I do not cover parts of os that exist only on one
#           kind of platform, nor do I cover platform-specific modules. All
#           functionality covered in this book is available at least on both
#           'posix' and 'nt' platforms. However, I do cover any differences
#           among the ways in which a given functionality is provided on
#           different platforms.


#    https://docs.python.org/3.1/library/os.html#process-parameters
#    Process Parameters
'''
os.environ
os.chdir(path)
os.fchdir(fd)
os.getcwd()
os.ctermid()
os.getegid()
os.geteuid()
os.getgid()
os.getgroups()
os.getlogin()
os.getpgid(pid)
os.getpgrp()
os.getpid()
os.getppid()
os.getuid()
os.getenv(varname[, value])
os.putenv(varname, value)
os.setegid(egid)
os.seteuid(euid)
os.setgid(gid)
os.setgroups(groups)
os.setpgrp()
os.setpgid(pid, pgrp)
os.setreuid(ruid, euid)
os.setregid(rgid, egid)
os.getsid(pid)
os.setsid()
os.setuid(uid)
os.strerror(code)
os.umask(mask)
os.uname()
os.unsetenv(varname)
'''

#    https://docs.python.org/3.1/library/os.html#file-object-creation
#    File Object Creation
'''
os.fdopen(fd[, mode[, bufsize]])
'''

#    https://docs.python.org/3.1/library/os.html#file-descriptor-operations
#    File Descriptor Operations
'''
os.close(fd)
os.closerange(fd_low, fd_high)
os.device_encoding(fd)
os.dup(fd)
os.dup2(fd, fd2)
os.fchmod(fd, mode)
os.fchown(fd, uid, gid)
os.fdatasync(fd)
os.fpathconf(fd, name)
os.fstat(fd)
os.fstatvfs(fd)
os.fsync(fd)
os.ftruncate(fd, length)
os.isatty(fd)
os.lseek(fd, pos, how)
    os.SEEK_SET
    os.SEEK_CUR
    os.SEEK_END
os.open(file, flags[, mode])
os.openpty()
os.pipe()
os.read(fd, n)
os.tcgetpgrp(fd)
os.tcsetpgrp(fd, pg)
os.ttyname(fd)
os.write(fd, str)
'''

#    https://docs.python.org/3.1/library/os.html#files-and-directories
#    File and Directories
'''
os.access(path, mode)
    os.F_OK
    os.R_OK
    os.W_OK
    os.X_OK
os.chdir(path)
os.fchdir(fd)
os.getcwd()
os.getcwdb()
os.chflags(path, flags)
os.chroot(path)
os.chmod(path, mode)
os.chown(path, uid, gid)
os.lchflags(path, flags)
os.lchmod(path, mode)
os.lchown(path, uid, gid)
os.link(source, link_name)
os.listdir(path)
os.lstat(path)
os.mkfifo(path[, mode])
os.mknod(filename[, mode=0o600, device])
os.major(device)
os.minor(device)
os.makedev(major, minor)
os.mkdir(path[, mode])
os.makedirs(path, mode=0o777)
os.pathconf(path, name)
os.pathconf_names
os.readlink(path)
os.remove(path)
os.removedirs(path)
os.rename(src, dst)
os.renames(old, new)
os.rmdir(path)
os.stat(path)
os.stat_float_times([newvalue])
os.statvfs(path)
os.symlink(source, link_name)
os.unlink(path)
os.utime(path, times)
os.walk(top[, topdown=True[, onerror=None[, followlinks=False]]])
'''

#    https://docs.python.org/3.1/library/os.html#process-management
#    Process Management
'''
os.abort()
os.execl(path, arg0, arg1, ...)
os.execle(path, arg0, arg1, ..., env)
os.execlp(file, arg0, arg1, ...)
os.execlpe(file, arg0, arg1, ..., env)
os.execv(path, args)
os.execve(path, args, env)
os.execvp(file, args)
os.execvpe(file, args, env)
os._exit(n)
os.fork()
os.forkpty()
os.kill(pid, sig)
os.killpg(pgid, sig)
os.nice(increment)
os.plock(op)
os.popen(...)
os.spawnl(mode, path, ...)
os.spawnle(mode, path, ..., env)
os.spawnlp(mode, file, ...)
os.spawnlpe(mode, file, ..., env)
os.spawnv(mode, path, args)
os.spawnve(mode, path, args, env)
os.spawnvp(mode, file, args)
os.spawnvpe(mode, file, args, env)
os.startfile(path[, operation])
os.system(command)
os.times()
os.wait()
os.waitpid(pid, options)
os.wait3([options])
os.wait4(pid, options)
'''


#    https://docs.python.org/3.1/library/os.html#miscellaneous-system-information
#    Miscellaneous System Information
'''
os.confstr(name)
os.confstr_names
os.getloadavg()
os.sysconf(name)
os.sysconf_names
os.curdir
os.pardir
os.sep
os.altsep
os.extsep
os.pathsep
os.defpath
os.linesep
os.devnull
'''

#    https://docs.python.org/3.1/library/os.html#miscellaneous-functions
#    Miscellaneous Functions
'''
os.urandom(n)
'''


#    Now couple of examples to satify the curiosity.
import os

print ("----------")
print ("os.environ")

count = 0
for entry in os.environ:
    print ("%d) %s=" % (count, entry), os.environ[entry])
    count += 1                # 0) IMSETTINGS_INTEGRATE_DESKTOP= yes
                              # 1) XDG_SESSION_DESKTOP= cinnamon
                              # 2) SERVER=
                              # 3) QTINC= /usr/lib64/qt-3.3/include
                              # 4) GDMSESSION= cinnamon
                              # 5) HISTSIZE= 1000
                              # etc ...

print ("----------")
print ("os.getcwd()=", os.getcwd())          # /home/mihai/Code/git-main/tutorial/
print ("os.getlogin()=", os.getlogin())      # mihai
try:
    print ("os.getuid()=", os.getuid())      # 1000
except:
    print ("os has not attribute getuid()");

print ("os.listdir('.')=\n", os.listdir('.'))  # ['19_module_getpass.py',
                                               #  '01_file_builtin_type.py'
                                               #  '09_module_tarfile.py',
                                               #  '05_module_struct.py', etc...

if os.path.exists('./temp_os_dir'):
    pass
else:
    os.mkdir('./temp_os_dir')

if 'temp_os_dir' in os.listdir('.'):
    print ("found temp_os_dir in os.listdir('.')")  # found temp_os_dir...
    if os.path.isdir('./temp_os_dir'):
        print ("./temp_os_dir is a directory")      # ./temp_os_dir is a dir...
        os.rmdir('./temp_os_dir')
        print ("removed ./temp_os_dir")             # removed ./temp_os_dir
