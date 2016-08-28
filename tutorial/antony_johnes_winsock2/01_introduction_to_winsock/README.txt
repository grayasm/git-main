*
*
**** Capter 1. Introduction to Winsock ****

	Winsock is available in two major versions: Winsock 1 and Winsock 2
	on all Windows platforms except Windows CE (Windows CE has only Winsock 1).

	For compatibility with older Winsock applications and when developing on 
	Windows CE platforms, WINSOCK.H is available.
	There is also an additional header file: MSWSOCK.H, which targets 
	Microsoft-specific programming extensions that are normally used for
	developing high performance Winsock applications, which will be described in
	Chapter 6. 

	When compiling your application with WINSOCK2.H, you should link with WS2_32.LIB library.
	When using WINSOCK.H (as on Windows CE) you should use WSOCK32.LIB. 
	If you use extension APIs from MSWSOCK.H, you must also link with MSWSOCK.DLL.

	Once you have included the necessary header files and link environment,
	you are ready to begin coding your application, which requires initializing
	Winsock. 

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
	
	Server API
	----------
	socket(af, type, protocol) : SOCKET
			a SOCKET type in Winsock2.h is a HANDLE to a transport provider,
			but different than a FILE handle, so a different type.
			af - the protocol family address (AF_INET for IPv4)
			type - the protocol socket type (SOCK_STREAM, SOCK_DGRAM)
			protocol - the protocol (IPPROTO_TCP, IPPROTO_UDP)

	bind(SOCKET s, const struct sockaddr FAR* name, int namelen) : int
			Once the socket of a particular protocol is created, you must bind
			it to a well-known address (interface, address and port).
			
			On error, bind returns SOCKET_ERROR. The most common error 
			encountered with bind is WSAEADDRINUSE.
			With TCP/IP, the WSAEADDRINUSE error indicates that another process 
			is already bound to the local IP interface and port number or that 
			the IP interface and port number are in the TIME_WAIT state.
			If you call bind again on a socket that is already bound, WSAEFAULT 
			will be returned.

	listen(SOCKET s, int backlog) : int
			The bind function merely associates the socket with a given address.
			The API function that tells a socket to wait for incoming
			connections is listen.
			It takes as parameters a socket and a backlog which is the maximum
			number of simultan requests (pending queue) that the server accepts.
			backlog + 1 request will fail with WSAECONNREFUSED.
			Once the server accepts a connection, the request is removed from 
			the queue so that others can make a request.
			
			The backlog parameter is silently limited to a value that the 
			underlying protocol provider determines. Illegal values are replaced 
			with their nearest legal values. In addition, there is no standard 
			provision for finding the actual backlog value. 
			
			Error WSAEINVAL, which usually indicates that you forgot to call
			bind before listen.
			Error WSAEADDRINUSE on the listen call as opposed to the bind call. 
			This error occurs most often on the bind call.
			
	accept(SOCKET s, struct sockaddr FAR* addr, int FAR* addrlen) : SOCKET
			Each call accepts 1 client connection only.
			s - is the listening socket
			addr and addrlen - the accepted client request address + size.
			returned SOCKET - the accepted client SOCKET descriptor for all 
			subsequent operations with that client.
			
			The original listening socket is still open to accept other client 
			connections and is still in listening mode.
			
			If an error occurs, INVALID_SOCKET is returned. 
			The most common error encountered is WSAEWOULDBLOCK if the listening 
			socket is in asynchronous or non-blocking mode and there is no 
			connection to be accepted.
	
	Client API
	----------
	connect(SOCKET s, const struct sockaddr FAR* name, int namelen) : int
			s - the valid TCP socket on which to establish the connection
			name - the socket address structure (SOCKADDR_IN) for TCP that 
			       describes the server to connect to
		    name - len is the length of the name variable.

			If the computer you're attempting to connect to does not have a 
			process listening on the given port, the connect call fails with 
			the WSAECONNREFUSED error. 
			The other error you might encounter is WSAETIMEDOUT, which occurs 
			if the destination you're trying to reach is unavailable 
			(either because of a communication-hardware failure on the route 
			to the host or because the host is not currently on the network).

			
	TCP States   (action) [SOCKET STATE] {PACKET}
	=================================================
	
	Client initializes and establishes a connection.
	SERVER                                     CLIENT
	-------------------------+------------------------
	[LISTEN]                             [CLOSED]
                            <--    {SYN} [SYN_SENT]
	[SYN_RCVD] {SYN_ACK}    -->
                            <--    {ACK} [ESTABLISHED]
	[ESTABLISHED]

	Client closes the socket while server being busy sends first ACK and then
	after short time FIN to signal it is closing the connection too.
	SERVER                                     CLIENT
	-------------------------+-----------------------
	                        <--    {FIN} [FIN_WAIT_1]
	            {ACK}       -->
										 [FIN_WAIT_2]
				{FIN}       -->
				            <--    {ACK} [TIME_WAIT]
							             (2 x MSL)
										 [CLOSED]

    The TIME_WAIT state is also called the 2MSL wait state.
	MSL stands for Maximum Segment Lifetime and represents the amount of time a
	packet can exist on the network before being discarded. Each IP packet has a
	time-to-live (TTL) field, which when decremented to 0 causes the packet 
	to be discarded. Each router on the network that handles the packet 
	decrements the TTL by 1 and passes the packet on. Once an application enters 
	the TIME_WAIT state, it remains there for twice the MSL time.
	This allows TCP to re-send the final ACK in case it's lost, causing the FIN 
	to be retransmitted. After the 2MSL wait state completes, the socket goes 
	to the CLOSED state.
	
	
	Client closes the socket and server responds with FIN.
	SERVER                                     CLIENT
	-------------------------+-----------------------
	                        <--    {FIN} [FIN_WAIT_1]
	            {FIN}       -->
				            <--    {ACK} [CLOSING]
			    {ACK}       -->
				                         [TIME_WAIT]
							             (2 x MSL)
										 [CLOSED]										 
	
	Client closes the socket and server reposes with FIN_ACK.
    SERVER                                     CLIENT
	-------------------------+-----------------------
	                        <--    {FIN} [FIN_WAIT_1]
	            {FIN_ACK}   -->
				            <--    {ACK} [TIME_WAIT]
							             (2 x MSL)
										 [CLOSED]		
	
	
	Passive closure when server closes the connection by sending FIN.
    SERVER                                     CLIENT
	-------------------------+-----------------------
	            {FIN}       -->
				            <--    {ACK} [CLOSE_WAIT]
							<--    {FIN} [LAST_ACK]
			    {ACK}       -->
							             [CLOSED]		
		
	For more information about TCP/IP protocol, RFC 793 at http://www.rfc-editor.org. 
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	