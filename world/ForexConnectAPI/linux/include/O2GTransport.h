#pragma once

#ifndef WIN32
#ifndef INFINITE
#define INFINITE 0xFFFFFFF
#endif
#endif

class Order2Go2 CO2GTransport
{
 public:
    /** Create transport session.*/
    static IO2GSession* createSession();

    /** Set proxy.
        @param proxyHost            Proxy host.
        @param iPort                Proxy port.
        @param user                 User name.
        @param password             User password.
    */
    static void setProxy(const char* proxyHost, int port, const char* user, const char* password);

    /** Set CA info (Useless in Windows OS)
        @param caFilePath           File path to certificate (certificate bundle) in PEM format.
    */
    static void setCAInfo(const char* caFilePath);

    /** Set number of reconnection tries
    @param iNumber              Number of reconnection tries.
    */
    static void setNumberOfReconnections(const unsigned int number);
    /** Set application id.*/
    static void setApplicationID(const char* applicationID);
    /** Get appalication id.*/
    static void getApplicationID(char* applicationID, size_t &len);
 
};

