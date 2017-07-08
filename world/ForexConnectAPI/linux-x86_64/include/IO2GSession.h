#pragma once

class Order2Go2 IO2GSessionDescriptor : public IAddRef
{
 protected:
    IO2GSessionDescriptor();
 public:
    /** Gets the unique identifier of the descriptor. */
    virtual const char * getID() = 0;
    /** Gets the readable name of the descriptor. */
    virtual const char *getName() = 0;
    /** Gets the description of the descriptor. */
    virtual const char *getDescription() = 0;

    virtual bool requiresPin() = 0;
};

class Order2Go2 IO2GSessionDescriptorCollection : public IAddRef
{
 protected:
    IO2GSessionDescriptorCollection();
 public:
    /** Gets number of session descriptors. */
    virtual int size() = 0;
    /** Gets the session descriptor by index.*/
    virtual IO2GSessionDescriptor *get(int index) = 0;
};

class Order2Go2 IO2GSessionStatus : public IAddRef
{
 protected:
    IO2GSessionStatus();
 public:
    typedef enum
    {
        Disconnected = 0,
        Connecting = 1,
        TradingSessionRequested = 2,
        Connected = 3,
        Reconnecting = 4,
        Disconnecting = 5,
        SessionLost = 6,
        PriceSessionReconnecting = 7,
        ConnectedWithNeedToChangePassword = 8,
        ChartSessionReconnecting = 9,
    } O2GSessionStatus;

    virtual void onSessionStatusChanged(O2GSessionStatus status) = 0;
    virtual void onLoginFailed(const char *error) = 0;
};

class Order2Go2 IO2GChartSessionStatus : public IAddRef
{
 protected:
    IO2GChartSessionStatus();
 public:
    typedef enum
    {
        Disconnected = 0,
        Connecting = 1,        
        Connected = 3,
        Reconnecting = 4,
        Disconnecting = 5,
        SessionLost = 6,        
    } O2GChartSessionStatus;

    virtual void onChartSessionStatusChanged(O2GChartSessionStatus status) = 0;
    virtual void onChartSessionLoginFailed(const char *error) = 0;
};

class Order2Go2 IO2GTableManagerListener : public IAddRef
{
 protected:
    IO2GTableManagerListener();
 public:
    virtual void onStatusChanged(O2GTableManagerStatus status, IO2GTableManager *tableManager) = 0;
};

class Order2Go2 IO2GSystemPropertiesListener : public IAddRef
{
 protected:
    IO2GSystemPropertiesListener();
 public:
    virtual void onChangeProperty(const char *propertyName, const char *propertyValue) = 0;
};

class Order2Go2 IO2GSession : public IAddRef
{
 protected:
    IO2GSession();
 public:
    virtual IO2GLoginRules *getLoginRules() = 0;
    /** Establishes connection with the trade server.*/
    virtual void login(const char *user, const char *pwd, const char *url, const char *connection) = 0;
    /** Closes connection with the trade server.*/
    virtual void logout() = 0;
    /* Subscribes the session status listener.*/
    virtual void subscribeSessionStatus(IO2GSessionStatus *listener) = 0;
    /* Unsubscribes the session status listener.*/
    virtual void unsubscribeSessionStatus(IO2GSessionStatus *listener) = 0;
    /** Gets the session descriptors collection.*/
    virtual IO2GSessionDescriptorCollection *getTradingSessionDescriptors() = 0;
    /** Sets the trading session identifier and pin.*/
    virtual void setTradingSession(const char *sessionId, const char *pin) = 0;
    /** Subscribes response listener.*/
    virtual void subscribeResponse(IO2GResponseListener *listener) = 0;
    /** Unsubscribes response listener.*/
    virtual void unsubscribeResponse(IO2GResponseListener *listener) = 0;
    /** Subscribes system properties changes.*/
    virtual void subscribeSystemPropertiesChange(IO2GSystemPropertiesListener *listener) = 0;
    /** Unsubscribes system properties changes.*/
    virtual void unsubscribeSystemPropertiesChange(IO2GSystemPropertiesListener *listener) = 0;
    /** Get the request factory.*/
    virtual IO2GRequestFactory * getRequestFactory() = 0 ;
    /** Gets the response factory reader.*/
    virtual IO2GResponseReaderFactory *getResponseReaderFactory() = 0;
    /** Send the request to the trade server.*/
    virtual void sendRequest(IO2GRequest *request) = 0;
    /** Set timeout(ms) for all requests.*/
    virtual void setRequestsTimeout(size_t timeout) = 0;
    /** Get timeout(ms) for all requests.*/
    virtual size_t getRequestsTimeout() = 0;
    /** Gets time converter for converting request and markes snapshot date.*/
    virtual IO2GTimeConverter *getTimeConverter() = 0;
    /** Set session mode.*/
    virtual void setPriceUpdateMode(O2GPriceUpdateMode mode) = 0;
    /** Get session mode.*/
    virtual O2GPriceUpdateMode getPriceUpdateMode() = 0;
    /** Get server time.*/
    virtual DATE getServerTime() = 0;    

    /** Get table manager.*/
    virtual IO2GTableManager *getTableManager() = 0;

    /** Get table manager by account.*/
    virtual IO2GTableManager *getTableManagerByAccount(const char *accountID) = 0;

    /** Set how to use table manager.*/
    virtual void useTableManager(O2GTableManagerMode mode, IO2GTableManagerListener *tablesListener) = 0;

    /** Gets current session status.*/
    virtual IO2GSessionStatus::O2GSessionStatus getSessionStatus() = 0;

    /** Set price refresh rate (ms).*/
    virtual bool setPriceRefreshRate(int priceRefreshRate) = 0;
    /** Get price refresh rate (ms).*/
    virtual int getPriceRefreshRate() = 0;
    /** Get minimum price refresh rate (ms).*/
    virtual int getMinPriceRefreshRate() = 0;
    /** Get maximum price refresh rate (ms).*/
    virtual int getMaxPriceRefreshRate() = 0;
    
    /** Gets session sub ID. */
    virtual const char* getSessionSubID() = 0;

    /** Sets the mode of the chart session. The method should be called before login. */
    virtual void setChartSessionMode(O2GChartSessionMode mode) = 0;
    /** Gets the mode of the chart session. */
    virtual O2GChartSessionMode getChartSessionMode() = 0;
    /* Subscribes the chart session status listener.*/
    virtual void subscribeChartSessionStatus(IO2GChartSessionStatus * listener) = 0;
    /* Unsubscribes the chart session status listener.*/
    virtual void unsubscribeChartSessionStatus(IO2GChartSessionStatus * listener) = 0;
    /** Gets current chart session status.*/
    virtual IO2GChartSessionStatus::O2GChartSessionStatus getChartSessionStatus() = 0;

    /** Gets current user kind*/
    virtual O2GUserKind getUserKind() = 0;
    /** Gets user name. */
    virtual const char* getUserName() = 0;

    /** Gets the commissions provider */
    virtual IO2GCommissionsProvider* getCommissionsProvider() = 0;

    /** The method starts the logging out, waiting until it is completed and close the session object.
    */
    virtual void forceClose() = 0;
};

