#pragma once

class IO2GSession;
class CProxyConfig;

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

class IPriceHistoryCommunicator;
class IError;

/** A factory of IPriceHistoryCommunicator objects.

 */
class HIST_PRICE_API PriceHistoryCommunicatorFactory
{
 public:
    /** Set globally proxyCofig object (see also another overloaded setProxy(..) variant)

        NOTE: the settings will be applied only for new IPriceHistoryCommunicator instances

        @param proxyCfg
            - a proxy config object. It will be copied.
            - NULL if the proxy settings should be reseted
   
     */
    static void setProxy(CProxyConfig *proxyCfg);

    /** Sets proxy configuration settings (see also setProxy(CProxyConfig *proxyCfg) variant )

        NOTE: the settings will be applied only for new IPriceHistoryCommunicator instances

        @param proxyHost
            proxy host

        @param iPort
            proxy port

        @param user
            proxy username

        @param password
            proxy password
     */
    static void setProxy(const char *proxyHost, int port, const char *user, const char *password);

    /** Creates a communicator instance.

        @param o2gSession
            The initialized ForexConnect session object
        @param quotesManagerDataPath
            A path to a local Quotes storage. Local QuotesCatalog and QuotesCache files 
            are stored under this path.
            - On Windows this string must be in the current system Windows ANSI code page (CP_ACP);
            - On Linux it must be in the UTF8 encoding.
            It means that in most cases no special conversions are required to prepare this string.
        @param error
            [output] If not NULL and an error occurred it will contain a pointer to a 
            detailed error description object. It must be released by a caller after the use.
        @return
            The method returns a new communicator instance. If an error occurred returns NULL,
            in this case error output parameter (if not NULL) contains a pointer to a detailed 
            error description object
     */
    static IPriceHistoryCommunicator* createCommunicator(IO2GSession *o2gSession,
                                                         const char *quotesManagerDataPath,
                                                         IError **error);
};

}
