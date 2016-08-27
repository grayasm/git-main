

Winsock is available in two major versions: Winsock 1 and Winsock 2
on all Windows platforms except Windows CE (Windows CE has only Winsock 1).

For compatibility with older Winsock applications and when developing on 
Windows CE platforms, WINSOCK.H is available.
There is also an additional header file: MSWSOCK.H, which targets Microsoft-specific programming 
extensions that are normally used for developing high performance Winsock applications, 
which will be described in Chapter 6. 

When compiling your application with WINSOCK2.H, you should link with WS2_32.LIB library.
When using WINSOCK.H (as on Windows CE) you should use WSOCK32.LIB. 
If you use extension APIs from MSWSOCK.H, you must also link with MSWSOCK.DLL.

Once you have included the necessary header files and link environment,
you are ready to begin coding your application, which requires initializing Winsock. 

IPC Stocket client - server 
===============================
SERVER      |       CLIENT
------------+------------------
socket()            socket()
bind()
listen()
accept()
            <--     connect()
read()      <--     write()
write()     -->     read()