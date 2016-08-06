/*
 * EchoSrv.c
 *
 * Sample code for Multithreading Applications in Win32
 * This is from Chapter 6, Listing 6-4
 *
 * Demonstrates how to use I/O completion ports
 * with TCP on the Internet.  This sample
 * server can only be run on Windows NT,
 * version 3.51 or later.  The client (EchoCli)
 * can be run on Windows 95.
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <winsock.h>
#include <io.h>
#include "MtVerify.h"

// Pick a port number that seems to be away from all others
#define SERV_TCP_PORT 5554
#define MAXLINE 512

//
// Structure definition
//

// The context key keeps track of how the I/O
// is progressing for each individual file handle.
struct ContextKey
{
    SOCKET  sock;
    // Input
    char        InBuffer[4];
    OVERLAPPED  ovIn;
    // Output
    int         nOutBufIndex;
    char        OutBuffer[MAXLINE];
    OVERLAPPED  ovOut;
    DWORD       dwWritten;
};

//
// Global variables
//

HANDLE ghCompletionPort;

//
// Function prototypes
//

void CreateWorkerThreads();
DWORD WINAPI ThreadFunc(LPVOID pvoid);
void IssueRead(struct ContextKey *pCntx);
void CheckOsVersion();
void FatalError(char *s);

///////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    SOCKET  listener;
    SOCKET  newsocket;
    WSADATA WsaData;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    int     clientAddressLength;
    int     err;

    CheckOsVersion();

    err = WSAStartup (0x0101, &WsaData);
    if (err == SOCKET_ERROR)
    {
        FatalError("WSAStartup Failed");
        return EXIT_FAILURE;
    }

    /*
     * Open a TCP socket connection to the server
     * By default, a socket is always opened
     * for overlapped I/O.  Do NOT attach this
     * socket (listener) to the I/O completion
     * port!
     */
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        FatalError("socket() failed");
        return EXIT_FAILURE;
    }

    /*
     * Bind our local address
     */
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port        = htons(SERV_TCP_PORT);

    err = bind(listener,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress)
          );
    if (err < 0)
        FatalError("bind() failed");

    ghCompletionPort = CreateIoCompletionPort(
            INVALID_HANDLE_VALUE,
            NULL,   // No prior port
            0,      // No key
            0       // Use default  # of threads
            );
    if (ghCompletionPort == NULL)
        FatalError("CreateIoCompletionPort() failed");

    CreateWorkerThreads(ghCompletionPort);

    listen(listener, 5);

    fprintf(stderr, "Echo Server with I/O Completion Ports\n");
    fprintf(stderr, "Running on TCP port %d\n", SERV_TCP_PORT);
    fprintf(stderr, "\nPress Ctrl+C to stop the server\n");

    //
    // Loop forever accepting requests new connections
    // and starting reading from them.
    //
    for (;;)
    {
        struct ContextKey *pKey;

        clientAddressLength = sizeof(clientAddress);
        newsocket = accept(listener,
                            (struct sockaddr *)&clientAddress,
                            &clientAddressLength);
        if (newsocket < 0)
        {
            FatalError("accept() Failed");
            return EXIT_FAILURE;
        }

        // Create a context key and initialize it.
        // calloc will zero the buffer
        pKey = calloc(1, sizeof(struct ContextKey));
        pKey->sock = newsocket;
        pKey->ovOut.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Set the event for writing so that packets
        // will not be sent to the completion port when
        // a write finishes.
        pKey->ovOut.hEvent = (HANDLE)((DWORD)pKey->ovOut.hEvent | 0x1);

        // Associate the socket with the completion port
        CreateIoCompletionPort(
                (HANDLE)newsocket,
                ghCompletionPort,
                (DWORD)pKey,   // No key
                0              // Use default # of threads
            );

        // Kick off the first read
        IssueRead(pKey);
    }
    return 0;
}

void CreateWorkerThreads()
{
    SYSTEM_INFO  sysinfo;
    DWORD        dwThreadId;
    DWORD        dwThreads;
    DWORD        i;

    GetSystemInfo(&sysinfo);
    dwThreads = sysinfo.dwNumberOfProcessors * 2 + 2;
    for (i=0; i<dwThreads; i++)
    {
        HANDLE hThread;
        hThread = CreateThread(
            NULL, 0, ThreadFunc, NULL, 0, &dwThreadId
            );
        CloseHandle(hThread);
    }
}

//
// Each worker thread starts here.
DWORD WINAPI ThreadFunc(LPVOID pVoid)
{
    BOOL    bResult;
    DWORD   dwNumRead;
    struct ContextKey *pCntx;
    LPOVERLAPPED lpOverlapped;

    UNREFERENCED_PARAMETER(pVoid);

    // Loop forever on getting packets from
    // the I/O completion port.
    for (;;)
    {
        bResult = GetQueuedCompletionStatus(
               ghCompletionPort,
               &dwNumRead,
               &(DWORD)pCntx,
               &lpOverlapped,
               INFINITE
            );

        if (bResult == FALSE
            && lpOverlapped == NULL)
        {
            FatalError(
                "ThreadFunc - Illegal call to GetQueuedCompletionStatus");
        }

        else if (bResult == FALSE
            && lpOverlapped != NULL)
        {
            // This happens occasionally instead of
            // end-of-file. Not sure why.
            closesocket(pCntx->sock);
            free(pCntx);
            fprintf(stderr,
                "ThreadFunc - I/O operation failed\n");
        }

        else if (dwNumRead == 0)
        {
            closesocket(pCntx->sock);
            free(pCntx);
            fprintf(stderr, "ThreadFunc - End of file.\n");
        }

        // Got a valid data block!
        // Save the data to our buffer and write it
        // all back out (echo it) if we have see a \n
        else
        {
            // Figure out where in the buffer to save the character
            char *pch = &pCntx->OutBuffer[pCntx->nOutBufIndex++];
            *pch++ = pCntx->InBuffer[0];
            *pch = '\0';    // For debugging, WriteFile doesn't care
            if (pCntx->InBuffer[0] == '\n')
            {
                WriteFile(
                        (HANDLE)(pCntx->sock),
                        pCntx->OutBuffer,
                        pCntx->nOutBufIndex,
                        &pCntx->dwWritten,
                        &pCntx->ovOut
                    );
                pCntx->nOutBufIndex = 0;
                fprintf(stderr, "Echo on socket %x.\n", pCntx->sock);
            }

            // Start a new read
            IssueRead(pCntx);
        }
    }

    return 0;
}


/*
 * Call ReadFile to start an overlapped request
 * on a socket.  Make sure we handle errors
 * that are recoverable.
 */
void IssueRead(struct ContextKey *pCntx)
{
    int     i = 0;
    BOOL    bResult;
    int     err;
    int     numRead;

    while (++i)
    {
        // Request a single character
        bResult = ReadFile(
                    (HANDLE)pCntx->sock,
                    pCntx->InBuffer,
                    1,
                    &numRead,
                    &pCntx->ovIn
                );

        // It succeeded immediately, but do not process it
        // here, wait for the completion packet.
        if (bResult)
            return;

        err = GetLastError();

        // This is what we want to happen, it's not an error
        if (err == ERROR_IO_PENDING)
            return;

        // Handle recoverable error
        if ( err == ERROR_INVALID_USER_BUFFER ||
             err == ERROR_NOT_ENOUGH_QUOTA ||
             err == ERROR_NOT_ENOUGH_MEMORY )
        {
            if (i == 5) // I just picked a number
            {
                Sleep(50);  // Wait around and try later
                continue;
            }

            FatalError("IssueRead - System ran out of non-paged space");
        }

        break;
    }

    fprintf(stderr, "IssueRead - ReadFile failed.\n");
}

//
// Make sure we are running under the right versions
// of Windows NT (3.51, 4.0, or later)
//
void CheckOsVersion()
{
    OSVERSIONINFO   ver;
    BOOL            bResult;

    ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    bResult = GetVersionEx((LPOSVERSIONINFO) &ver);

    if ( (!bResult) ||
         (ver.dwPlatformId != VER_PLATFORM_WIN32_NT) )
    {
        FatalError("ECHOSRV requires Windows NT 3.51 or later.");
    }

}

//
// Error handler
//
void FatalError(char *s)
{
    fprintf(stdout, "%s\n", s);
    exit(EXIT_FAILURE);
}
