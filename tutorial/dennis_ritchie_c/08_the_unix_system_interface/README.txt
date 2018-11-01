.
                      Cap.8 The UNIX System Interface
                      pag. 169 - 190

  1. The UNIX operating system provides its services through a set of system
     calls, which are in effect functions within the operating system that may
     be called by user programs.
  2. the user of a program can redirect I/O to and from files with < and >
     prog <infile >outfile
  3. low level read/write use file descriptors, and system calls
     int bytes_ = read(int fd, char *buf, int bytes);
     int bytes_ = write(int fd, char *buf, int bytes);
  4. you must explicitly open files in order to read/write them
     #define PERMS 0666 /* RW for owner, group, others */
     int fd = open(char *name, int flags, int perms);
     int fd = creat(char *name, int perms);
     close(fd);
     unlink(char *name);
  5. for random access in a file without reading/writing any data we use:
     long bytes = lseek(int fd, long offset, int origin);
  6. files in standard library are described by file pointers FILE* rather then
     file descriptors int fd
     see pag.177 for an fopen implementation using open,creat,lseek with default
     0666 file permissions
  7. to list directories use
     DIR* opendir(char *dirname);
     Dirent* readdir(DIR *dfd);
     void closedir(DIR *dfd);
     int stat(char *name, struct stat *stbuf);
  8. char* sbrk(int n)
     is the UNIX system call that returns a pointer to n more bytes of storage.
     sbrk returns -1 if there was no space, which must be cast to char* to be
     compared with the return value.
  9. the storage returned by malloc must be aligned properly for the objects
     that will be stored in it. For each machine there is a most restrictive
     type: if the most restrictive type can be stored at a particular address,
     all other types may be also. On some machines, the most restrictive type
     is a double; on others int or long suffices.
     see pag.185 for a malloc example calling sbrk with proper alignment of
     memory blocks.
