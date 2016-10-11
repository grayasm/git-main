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

	IPC Stocket client - server (via TCP/IP)
	================+======================
	SERVER          |         CLIENT
	----------------+----------------------
	socket()                  socket()
	bind()
	listen()
	accept()
	               <--     connect()
	recv()         <--     send()
	send()         -->     recv()
	               <--     shutdown()
	closesocket()  -->
	               <--     closesocket()


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
			namelen - is the length of the name variable.

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


	Data Transmission.
	==================
	sending data:  send  WSASend
	receiving data: recv WSARecv

	All buffers associated with sending and receiving data are of the simple
	char type which is just simple byte-oriented data. In reality, it can be a
	buffer with any raw data in it—whether it's binary or string data doesn't
	matter.

	send(SOCKET s, const char FAR * buf, int len, int flags) : int
			Parameters are the socket, the buffer to send + its length and
			the flags (0, MSG_DONTROUTE, or MSG_OOB).
			MSG_DONTROUTE tells the transport not to route the packets.
			MSG_OOB is for transmiting out of band packets.
			The transport may or may not honor the passed flags.

			When an application on a connected stream socket needs to send data
			that is more important than regular data on the stream, it can mark
			the important data as out-of-band (OOB) data. The application on the
			other end of a connection can receive and process OOB data through a
			separate logical channel that is conceptually independent of the
			data stream. It is discouraged to use OOB as it is implementation
			specific and can differ on non-Windows systems.

			The errors are mostly related to the peer rebooting or connection
			dropped because of network failure or something else.

	recv(SOCKET s, char FAR* buf, int len, int flags) : int
			The parameters are the socket, the buffer to be filled and its size,
			and the flags (0, MSG_PEEK, or MSG_OOB).

			MSG_PEEK causes the data that is available to be copied into the
			supplied receive buffer, but this data is not removed from the
			system's buffer. The number of bytes pending is also returned.
			Message peeking is bad. Not only does it degrade performance, as you 
			now need to make two system calls (one to peek and one without the
			MSG_PEEK flag to actually remove the data), but it is also unreliable
			under certain circumstances. The data returned might not reflect the
			entire amount available. Also, by leaving data in the system buffers,
			the system has less space to contain incoming data. As a result, the
			system reduces the TCP window size for all senders. This prevents
			your application from achieving the maximum possible throughput.
			The best thing to do is to copy all the data you can into your own
			buffer and manipulate it there.

			There are some considerations when using recv on a
			(1) message-based socket (TCP) or (2) datagram-based socket (UDP).
			If the data pending is larger than the supplied buffer, the buffer
			is filled with as much data as it will contain. In this event, the
			recv call generates the error WSAEMSGSIZE. Note that the
			message-size error occurs with message-based protocols.
			Stream protocols such as TCP buffer incoming data and will return as
			much data as the application requests, even if the amount of pending
			data is greater. Thus, for streaming protocols you will not encounter
			the WSAEMSGSIZE error.


	Breaking the connection
	=======================

	To actually release the resources associated with an open socket handle,
	use the closesocket call. Be aware, however, that closesocket can have some
	adverse effects—depending on how it is called—that can lead to data loss.
	For this reason, a connection should be gracefully terminated with the
	shutdown function before a call to the closesocket function.

	shutdown(SOCKET s, int how) : int
			The how parameter can be SD_RECEIVE, SD_SEND, or SD_BOTH.
			For SD_RECEIVE, subsequent calls to any receive function on the
			socket are disallowed. This has no effect on the lower protocol
			layers. And for TCP sockets, if data is queued for receive or if
			data subsequently arrives, the connection is reset.
			However, on UDP sockets incoming data is still accepted and queued
			(because shutdown has no meaning for connectionless protocols).

			For SD_SEND, subsequent calls to any send function are disallowed.
			For TCP sockets, this causes a FIN packet to be generated after all
			data is sent and acknowledged by the receiver.

			Finally, specifying SD_BOTH disables both sends and receives.

	closesocket (SOCKET s) : int
			Calling closesocket releases the socket descriptor and any further
			calls using the socket fail with WSAENOTSOCK.
			If there are no other references to this socket, all resources
			associated with the descriptor are released.
			This includes discarding any queued data.


	Connectionless Communication (happens over UDP/IP)
	==================================================

	Connectionless communication behaves differently than connection-oriented
	communication, so the method for sending and receiving data is substantially
	different.
	In IP, connectionless communication is accomplished through UDP/IP.
	UDP doesn't guarantee reliable data transmission and is capable of sending
	data to multiple destinations and receiving it from multiple sources.
	For example, if a client sends data to a server, the data is transmitted
	immediately regardless of whether the server is ready to receive it. If the
	server receives data from the client, it doesn't acknowledge the receipt.
	Data is transmitted using datagrams, which are discrete message packets.

	IPC Stocket client - server (via UDP/IP) - first alternative.
	=====================+===================
	SERVER               |       CLIENT
	---------------------+------------------
	socket()                     socket()
	bind()
	recvfrom()          <--      sendto()
	                    <--      closesocket()
	closesocket()       -->


	IPC Stocket client - server (via UDP/IP) - second alternative.
	=====================+===================
	SERVER               |       CLIENT
	---------------------+------------------
	socket()                     socket()
	bind()                       connect()
	recvfrom()          <--      send()
	                    <--      closesocket()
	closesocket()       -->


	recvfrom(	SOCKET s, char FAR* buf, int len, int flags,
				struct sockaddr FAR* from, int FAR* fromlen) : int

			The difference with connectionless sockets is that you do not call
			listen or accept, but recvfrom, and you simply wait to receive the
			incoming data. Because there is no connection, the receiving socket
			can receive datagrams originating from any machine on the network.

			The first four parameters are the same as recv, including the
			possible values for flags: MSG_OOB and MSG_PEEK. The same warnings
			for using the MSG_PEEK flag also apply to connectionless sockets.
			The from parameter is a SOCKADDR structure for the given protocol of
			the listening socket, with fromlen pointing to the size of the
			address structure.
			When the API call returns with data, the SOCKADDR structure is
			filled with the address of the workstation that sent the data.

	sendto(	SOCKET s, const char FAR * buf, int len, int flags,
			const struct sockaddr FAR * to, int tolen) : int

			The parameters are the same as recvfrom except that buf is the
			buffer of data to send and len indicates how many bytes to send.
			Also, the to parameter is a pointer to a SOCKADDR structure with the
			destination address of the workstation to receive the data.
