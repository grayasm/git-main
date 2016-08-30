/*
 * https://msdn.microsoft.com/en-us/library/windows/desktop/ms738514(v=vs.85).aspx
 *
 * The gai_strerror function assists in printing error messages based on the 
 * EAI_* errors returned by the getaddrinfo function. 
 * Note that the gai_strerror function is not thread safe, and therefore, 
 * use of traditional Windows Sockets functions such as the WSAGetLastError
 * function is recommended.
 *
 * char* gai_strerror(_In_ int ecode);
 */