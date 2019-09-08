#pragma once

#include "IAddRef.h"
#ifndef WIN32
    #include <inttypes.h>
#endif

class CProxyConfig;

namespace gstool3
{
class ILogger;
}

namespace quotesmgr
{

#ifdef WIN32
    typedef __int64 int64;
#else
    typedef int64_t int64;
#endif

class IUpdateQuotesCatalogCallback;
class IRepairQuotesTaskCallback;
class IPrepareQuotesCallback;
class IReceiveBarQuotesCallback;
class IReceiveBarQuotesTask;
class IReceiveTickQuotesCallback;
class IRemoveQuotesCallback;
class IUpdateInstrumentsCallback;
class IError;
class IStringsLoader;
class IBaseTimeframes;

/** Possible modes how to process a weekend day candle. */
enum WeekendCandleMode
{
    WeekendCandleHide,
    WeekendCandleShow,
    WeekendCandleMergeToNextWeek
};

/** Possible modes how to consider candles open prices. */
enum OpenPriceCandlesMode
{
    OpenPricePrevClose = 0,
    OpenPriceFirstTick = 1
};

/** Instrument type enumeration*/
enum InstrumentType
{
    InstrumentTypeForex = 1,        //!< Regular forex instrument.
    InstrumentTypeIndices = 2,      //!< Indices.
    InstrumentTypeCommodity = 3,    //!< Commodities.
    InstrumentTypeTreasury = 4,     //!< Treasuries.
    InstrumentTypeBullion = 5,      //!< Bullion.   
    InstrumentTypeShares = 6,       //!< Shares
    InstrumentTypeFXIndex = 7,      //!< Index
    InstrumentTypeCFDShares = 8     //!< CFD Shares
};

//-----------------------------------------------------------------------------
// Task
//-----------------------------------------------------------------------------

/** Represents an abstract task that can be executed by a QuotesManager.
    Tasks are referable objects. When constructed mRef is equals to 1.
 */
class QUOTESMGR2_API Task : public IAddRef
{
 public:
    /** Task type. */
    enum Type
    {
        UpdateInstrumentsTask = 0,
        UpdateQuotesCatalogTask = 1,
        PrepareQuotesTask = 2,
        ReceiveBarQuotesTask = 3,
        RemoveQuotesTask = 4,
    };

    /** Adds a reference. */
    virtual long addRef() = 0;
    /** Releases a reference. */
    virtual long release() = 0;

    /** Gets a task type. Used internally. */
    virtual int getType() const = 0;

 protected:
     virtual ~Task() {};
};

//-----------------------------------------------------------------------------
// IUpdateQuotesCatalogTask
//-----------------------------------------------------------------------------
/** Represents task to update instruments 
    After the execution the following operations returns up-to-date values:
    - An instruments collection available on server (see IQuotesManager::getInstruments)

    Use IQuotesManager::createUpdateInstrumentsTask to create an instance.
    The object cannot be reused.
 */
class IUpdateInstrumentsTask : public Task
{
 public:
     /** Gets instrument catalog updater callback
     
      */
     virtual IUpdateInstrumentsCallback *getCallback() = 0;
};

//-----------------------------------------------------------------------------
// IUpdateInstrumentsCallback
//-----------------------------------------------------------------------------

/** A callback interface which receives notification when an instruments is updated.
    All methods may be called in an arbitrary internal thread.
 */
class IUpdateInstrumentsCallback : public IAddRef
{
 public:

    /** Callback is invoked when task is failed
        @param task 
            a task
        @param error
            error description
     */
     virtual void onTaskFailed(IUpdateInstrumentsTask *task, IError *error) = 0;

    /** Callback is invoked when task is completed succesfully
        @param task 
            a task
     */
    virtual void onTaskCompleted(IUpdateInstrumentsTask *task) = 0;

    /** Callback is invoked when task is cancelled
        @param task 
            a task
     */
    virtual void onTaskCanceled(IUpdateInstrumentsTask *task) = 0;

};

//-----------------------------------------------------------------------------
// IUpdateQuotesCatalogTask
//-----------------------------------------------------------------------------

/** Represents a task to update a local quotes catalog of an instrument.
    After the execution the following operations returns up-to-date values:
    - getting the oldest quote date;
    - is necessary to prepare quotes or not;
    - how many quotes would be downloaded during the prepare quotes task.
    Use IQuotesManager::createUpdateQuotesCatalogTask to create an instance.
    The object cannot be reused.
 */
class IUpdateQuotesCatalogTask : public Task
{
 public:
    /** Gets an instrument. */
    virtual const char* getInstrument() const = 0;

    /** Gets a timeframe. */
    virtual const char* getTimeframe() const = 0;

    /** Gets a task callback. */
    virtual IUpdateQuotesCatalogCallback* getCallback() = 0;
};

//-----------------------------------------------------------------------------
// IUpdateQuotesCatalogCallback
//-----------------------------------------------------------------------------

/** A callback interface which receives notification when a catalog is updated.
    All methods may be called in an arbitrary internal thread.
 */
class IUpdateQuotesCatalogCallback : public IAddRef
{
 public:
    /** Called when task execution is completed with an error.
        @param task a task
        @param error an error object
     */
    virtual void onTaskFailed(IUpdateQuotesCatalogTask *task, IError *error) = 0;

    /** Called when entire task execution is completed.
        @param task a task
     */
    virtual void onTaskCompleted(IUpdateQuotesCatalogTask *task) = 0;

    /** Called when a task execution was canceled.
        @param task a task
     */
    virtual void onTaskCanceled(IUpdateQuotesCatalogTask *task) = 0;
};

//-----------------------------------------------------------------------------
// IPrepareQuotesTask
//-----------------------------------------------------------------------------

/** Represents a task to prepare quotes of an instrument in some range.
    After the execution of the task quotes are available localy and can be
    received. Use IQuotesManager::createPrepareQuotesTask to create an instance.
    The object cannot be reused.
 */
class IPrepareQuotesTask : public Task
{
 public:
    /** Gets a total number of subtasks that should be executed. Can be used
        to determine progress of the task execution. The method may be used
        just after creation of the object.
     */
    virtual int getTotalSubtasks() const = 0;

    /** Gets an instrument. */
    virtual const char* getInstrument() const = 0;

    /** Gets a timeframe. */
    virtual const char* getTimeframe() const = 0;
    
    /** Gets a start date. */
    virtual double getStartDate() const = 0;

    /** Gets an end date. */
    virtual double getEndDate() const = 0;

    /** Gets a min number of quotes required. -1 if not used. */
    virtual int getQuotesCount() const = 0;

    /** Gets a task callback. 
    
        @return
            Callback pointer. The callback pointer should be released by the caller.
     */
    virtual IPrepareQuotesCallback* getCallback() = 0;
};

//-----------------------------------------------------------------------------
// IPrepareQuotesCallback
//-----------------------------------------------------------------------------

/** A callback interface which receives notifications about progress of a quotes
    prepare task. All methods may be called in an arbitrary internal thread.
 */
class IPrepareQuotesCallback : public IAddRef
{
 public:
    /** Called when a next subtask is executed. Either successful or with an
        error.

        @param task a task
        @param error if not null then contains an error, otherwise the 
            subtask completed successfully
     */
    virtual void update(IPrepareQuotesTask *task, IError *error) = 0;

    /** Called when entire task execution is completed.
        @param task a task
     */
    virtual void onTaskCompleted(IPrepareQuotesTask *task) = 0;

    /** Called when a task execution was canceled.
        @param task a task
     */
    virtual void onTaskCanceled(IPrepareQuotesTask *task) = 0;
};

//-----------------------------------------------------------------------------
// IReceiveBarQuotesTask
//-----------------------------------------------------------------------------

/** Represents a task to receive bar quotes of an instrument in some range.
    Use IQuotesManager::createReceiveBarQuotesTask to create an instance.
    The object cannot be reused.
 */
class IReceiveBarQuotesTask : public Task
{
 public:
    /** Gets an instrument. */
    virtual const char* getInstrument() const = 0;

    /** Gets a timeframe. */
    virtual const char* getTimeframe() const = 0;
    
    /** Gets a start date. */
    virtual double getStartDate() const = 0;

    /** Gets an end date. */
    virtual double getEndDate() const = 0;

    /** Gets a min number of quotes required. -1 if not used. */
    virtual int getQuotesCount() const = 0;

    /** Gets a task callback. 
        
        @return
            Callback pointer. The callback pointer should be released by the caller.
     */
    virtual IReceiveBarQuotesCallback* getCallback() = 0;
};

//-----------------------------------------------------------------------------
// IReceiveBarQuotesCallback
//-----------------------------------------------------------------------------

/** A callback interface which receives bar quotes as a result of 
    IReceiveBarQuotesTask execution. All methods may be called in an arbitrary 
    internal thread.
 */
class IReceiveBarQuotesCallback : public IAddRef
{
 public:
    /** Called for each received bar quote. Quotes are returned in backward order.
        @param task a task

     */
    virtual void nextBarQuote(IReceiveBarQuotesTask *task, double date,
                              double bidOpen, double bidHigh, 
                              double bidLow, double bidClose, double bidVolume,
                              double askOpen, double askHigh, 
                              double askLow, double askClose, double askVolume) = 0;

    /** Called when an entire task execution is completed.
        @param task a task
        @param lastMinute the last minute:
            - if not 0 then it's the last server defined minute on a moment when 
            a request has been executed. Note that probably it's not the current 
            server minute, it may be a historic minute if request's endDate != 0. 
            - if 0 it means that the the last received bar is ended before the current minute
            and lastMinute information is not available.
        @param lastMinuteVolume if lastMinute is not 0 then it's the current volume 
            (the number of ticks) in lastMinute on the moment of request execution. 
            If lastMinute is 0 then it's 0 too.
     */
    virtual void onTaskCompleted(IReceiveBarQuotesTask *task, double lastMinute,
        double lastMinuteVolume) = 0;

    /** Called when a task execution was canceled.
        @param task a task
     */
    virtual void onTaskCanceled(IReceiveBarQuotesTask *task) = 0;

    /** Called when task execution is completed with an error.
        @param task a task
        @param error an error object
     */
    virtual void onTaskFailed(IReceiveBarQuotesTask *task, IError *error) = 0;
};

//-----------------------------------------------------------------------------
// IRemoveQuotesTask
//-----------------------------------------------------------------------------

/** Represents a task to remove quotes of an instrument from internal storage in some range.
    Range is given by IRemoveQuotesTask::addYear method.
    Use IQuotesManager::createRemoveQuotesTask to create an instance.
    The object cannot be reused.
 */
class IRemoveQuotesTask : public Task
{
 public:

    /** Gets an instrument */
    virtual const char *getInstrument() const = 0;
    /** Gets a timeframe */
    virtual const char *getTimeframe() const = 0;
    
    /** Gets callback

        @return
            Callback pointer. The callback pointer should be released by the caller.
     */
    virtual IRemoveQuotesCallback *getCallback() const = 0;

    /** Adds year */
    virtual void addYear(int year) = 0;
    /** Gets year */
    virtual int getYear(int index) const = 0;
    /** Gets count of year */
    virtual int getYearsCount() const = 0;

    /** Gets a total number of subtasks that should be executed. Can be used
        to determine progress of the task execution. The method may be used
        just after creation of the object.
     */
    virtual int getTotalSubtasks() const = 0;

};

//-----------------------------------------------------------------------------
// IRemoveQuotesCallback
//-----------------------------------------------------------------------------

/** A callback interface which receives a result of 
    IRemoveQuotesTask execution.

 */
class IRemoveQuotesCallback : public IAddRef
{
 public:

   /** Called when a next subtask is executed.
       A task cancelling from this callback is not allowed.

       @param task a task
       @param error if not null then contains an error, otherwise the 
            subtask completed successfully
    */
   virtual void update(IRemoveQuotesTask *task, IError *error) = 0;

   /** Called when entire task execution is completed.
       @param task a task
    */
   virtual void onTaskCompleted(IRemoveQuotesTask *task) = 0;

   /** Called when a task execution was canceled.
        @param task a task
    */
   virtual void onTaskCanceled(IRemoveQuotesTask *task) = 0;
};

//-----------------------------------------------------------------------------
// IInstrument
//-----------------------------------------------------------------------------

/** The class provides access to the instrument information.

 */
class QUOTESMGR2_API IInstrument : public IAddRef
{
 public:

    /** Gets an instrument name */
    virtual const char *getName() = 0;
    /** Gets contract currency */
    virtual const char *getContractCurrency() = 0;
    /** Gets instrument precision */
    virtual int getPrecision() = 0;
    /** Gets instrument precision */
    virtual double getPointSize() = 0;

    /** Gets instrument type (see InstrumentType enum for codes definitions) */
    virtual int getInstrumentType() = 0;
    /** Gets instrument base unit size */
    virtual int getBaseUnitSize() = 0;
    /** Gets instrument contract multiplier */
    virtual int getContractMultiplier() = 0;

    /** Gets oldest available quote in archive-server
        @param timeframe
            the timeframe from base timeframes list (see IInstrument::getBaseTimeframes())
        @return
            oldest quote date avaialable for specofoed timeframe
     */
    virtual double getOldestQuoteDate(const char *baseTimeframe) = 0;
    /** Gets latest available quote in archive-server
        @param timeframe
            the timeframe from base timeframes list (see IInstrument::getBaseTimeframes())
        @return
            latest quote date avaialable for specofoed timeframe
     */
    virtual double getLatestQuoteDate(const char *baseTimeframe) = 0;

    /** Gets supported base timeframes by instrument */
    virtual IBaseTimeframes* getBaseTimeframes() = 0;

 protected:

    virtual ~IInstrument() { }
}; 

/** Represents instruments which are supported by the quotes manager.
 */
class QUOTESMGR2_API IInstruments : public IAddRef
{
 public:
    /** Gets count of instruments supported by the quotes manager. */
    virtual int size() const = 0;

    /** Gets instrument by index supported by the quotes manager.
        If index is unavailable then returns NULL.

        @return
            an instrument pointer (call IInstrument::release to release object)
            NULL - if index is unavailable
     */
    virtual IInstrument* get(int idx) const = 0;

    /** Finds instrument by name
        @return
            an instrument pointer (call IInstrument::release to release object)
            NULL - if not found
    
     */
    virtual IInstrument* find(const char *name) const = 0;

 protected:
     virtual ~IInstruments() { }

};

//-----------------------------------------------------------------------------
// IBaseTimeframes
//-----------------------------------------------------------------------------

/** Represents timeframes which are supported by the quotes manager. */
class QUOTESMGR2_API IBaseTimeframes : public IAddRef
{
 public:
    /** Gets count of timeframes supported by the quotes manager. */
    virtual int size() const = 0;

    /** Gets timeframe by index supported by the quotes manager.
        If index is unavailable then returns NULL.
     */
    virtual const char* get(int idx) const = 0;

 protected:
    virtual ~IBaseTimeframes() { }
};

//-----------------------------------------------------------------------------
// IQuotesManager
//-----------------------------------------------------------------------------

/** A QuotesManager interface.

    Use pricehistorymgr::IPriceHistoryCommunicator::getQuotesManager to create an
    instance.

    The quotes are requested by a combination of the following parameters: 
    FromDate, ToDate, MinCount. Dates parameters may be 0. It means:
    - if FromDate is 0 then some fixed number of quotes are requested. This is
        either MinCount if it specified, or default value (300);
    - if ToDate is 0 then it means "till now";
    MinCount may be omitted, in this case it should be -1 (zero or negative value also means -1)
    
    If both FromDate and MinCount are specified then one of conditions must be satisfied: resulting
    quotes must contain FromDate or MinCount of quotes is returned.
    All these rules are applied for prepare and receive tasks.

    QuotesManager works with quotes in EST timezone. It means that all quotes
    returned by QuotesManager are in EST timezone.

    How FromDate and ToDate are treated is demonstrated in the following examples:

    - A client requests m15 bars started from 16:50. In this case QuotesManager 
    rounds the FromDate to the period start (to 16:45) and then returns quotes 
    starting from this date. So the first bar will be 16:45 bar. 

    - A client requests m15 bars till 16:50. In this case QuotesManager rounds 
    the ToDate to the period start (to 16:45) and then returns quotes till this 
    date INCLUDING 16:45 bar. So the last received bar will be 16:45.

    Long-term opertioans are executed asynchronously and run as tasks. 
    Task execution perform global read or write lock. Quotes -dependent operations are required only read-lock. 
    There are many reader are possible and only one writer.
 */
class QUOTESMGR2_API IQuotesManager : public IAddRef
{
 public:
     /** Quotes preparation status. See areQuotesPrepared */
     enum QuotesPreparedStatus 
     {
        QuotesPrepared,            ///< all quotes are loaded
        QuotesPrepareRequired,    ///< partitialy loaded quotes case
        NoQuotes,                  ///< no quotes loaded at all
        OutOfCatalogRange        ///< Quotes cannot be loaded from archiveserver. (Also it means empty catalog)
     };

    /** Sets a weekend candle mode to use while processing requests.
        By default it's WeekendCandleShow.
        @param mode the new mode
     */
    virtual void setWeekendCandleMode(WeekendCandleMode mode) = 0;

    /** Gets current weeken candle mode 
         @return 
            current weekend mode
     */
    virtual WeekendCandleMode getWeekendCandleMode() const = 0;

    /** Sets a open price candles mode
        By default it's OpenPricePrevClose.
        @param mode the new mode
     */
    virtual void setOpenPriceCandlesMode(OpenPriceCandlesMode mode) = 0;

    /** Gets current open price candles mode.
        @return
            current open price candles mode
     */
    virtual OpenPriceCandlesMode getOpenPriceCandlesMode() const = 0;

    /** Is required to update a common instruments info

        @param error
            [out] error description

        @return false if update is required
            see error param if not NULL - error occurred
     */
    virtual bool areInstrumentsUpdated(IError **error = 0) = 0;

    /** Is required to update a quotes catalog of an instrument.

        @param instrument an instrument
        @param timeframe a timeframe
        @param error
            [out] error description

        @return false if update is required
            or error occurred (check *error value)
     */
    virtual bool isQuotesCatalogUpdated(const char *instrument, const char *timeframe,
        IError **error = 0) = 0;

    /** Gets a date of the latest quote available for specified timeframe for an instrument. It's server defined
        and may be not available localy w/o preparing.

        Returns a valid up-to-date result only when a local catalog is updated.

        @param instrument an instrument
        @param timeframe a timeframe
        @param error
            [out] error description

        @return a date or 0 if some error occurred
     */
    virtual double getLatestQuoteDate(const char *instrument, const char *timeframe,
        IError **error = 0) = 0;

    /** Gets a date of the oldest quote of an instrument. It's server defined
        and may be not available localy w/o preparing.
        Returns a valid up-to-date result only when a local catalog is updated.

        @param instrument an instrument
        @param timeframe a timeframe
        @param error
            [out] error description

        @return a date or 0 if some error occurred
     */
    virtual double getOldestQuoteDate(const char *instrument, const char *timeframe,
        IError **error = 0) = 0;
    
    /** Checks are quotes prepared (i.e. available in a LocalStorage).
        Returns a valid up-to-date result only when a local catalog is updated.

        @param instrument an instrument
        @param startDate start date of a range
        @param endDate end date of a range
        @param quotesCount a min number of quotes required, -1 if not used
            (zero or negative value also means -1)
        @param timeframe a timeframe
        @param amountToLoad [out] bytes to load, if loading is required.
            May return -1 if this information cannot be calculated.

        @param error
            [out] error description

        @return a status of quotes loaded in the LocalStorage in the specified
            dates range.
            NoQuotes - if there is no quotes or error occurred (see error parameter)

        NOTE: there can be differnet result for D1 depend on current WeekendCandleMode value
              when minCount is talen in account. This function try to build specified numbers of bars. 
              Because there can be different D1 bar a week depending on this param
     */
    virtual QuotesPreparedStatus areQuotesPrepared(const char *instrument, double startDate,
        double endDate, int quotesCount, const char *timeframe, 
        int *amountToLoad, IError **error = 0) = 0;

    /** Checks are quotes prepared (i.e. available in a LocalStorage).
        Returns a valid up-to-date result only when a local catalog is updated.

        @param instrument an instrument
        @param startDate start date of a range
        @param endDate end date of a range
        @param minCount a min number of quotes required, -1 if not used
                (zero or negative value also means -1)
        @param timeframe a timeframe

        @param error
            [out] error description

        @return true if quotes are prepared and can be got w/o execution of
            PrepareQuotesTask
            false - if there is no quotes or error (see error 'param' for details)

        NOTE: there can be differnet result for D1 depend on current WeekendCandleMode value
              when minCount is talen in account. This function try to build specified numbers of bars. 
              Because there can be different D1 bar a week depending on this param
     */
    virtual bool areQuotesPrepared(const char *instrument, double startDate,
        double endDate, int quotesCount, const char *timeframe, IError **error = 0) = 0;

    /** Creates an IUpdateInstrumentsTask instnace. 
        Returned instance is addRef-ed and
        must be released by a caller after usage.

        @param callback a callback pointer
        @param error
            [out] error description if error occurred

        @return
            a taks instance
            NULL - if any error occurred
     */
    virtual IUpdateInstrumentsTask* createUpdateInstrumentsTask(IUpdateInstrumentsCallback *callback, 
                                                                IError **error = 0) = 0; 

    /** Creates a UpdateQuotesCatalogTask instance. Returned instance is addRef-ed and
        must be released by a caller after usage.

        @param instrument an instrument
     */

    virtual IUpdateQuotesCatalogTask* createUpdateQuotesCatalogTask(const char *instrument, 
        const char *timeframe, IUpdateQuotesCatalogCallback *callback,
                                                                    IError **error = 0) = 0;

    /** Creates a PrepareQuotesTask instance. Returned instance is addRef-ed and
        must be released by a caller after usage.

        @param instrument an instrument
        @param startDate start date of a range
        @param endDate end date of a range
        @param minCount a min number of quotes required, -1 if not used
                (zero or negative value also means -1)
        @param timeframe a timeframe
     */
    virtual IPrepareQuotesTask* createPrepareQuotesTask(const char *instrument,
        double startDate, double endDate, int quotesCount, const char *timeframe, 
        IPrepareQuotesCallback *callback, IError **error = 0) = 0;

    /** Creates a ReceiveBarQuotesTask instance. Returned instance is addRef-ed and
        must be released by a caller after usage.

        @param instrument an instrument
        @param startDate start date of a range
        @param endDate end date of a range
        @param minCount a min number of quotes required, -1 if not used
         (zero or negative value also means -1)
        @param timeframe a timeframe

        @return
            new task instance
            NULL if invalid parameter. E.g: invalid timeframe (only bars allowed), endDate les than startDate 
     */
    virtual IReceiveBarQuotesTask* createReceiveBarQuotesTask(const char *instrument,
        double startDate, double endDate, int quotesCount, const char *timeframe, 
        IReceiveBarQuotesCallback *callback, IError **error = 0) = 0;

    /** Creates a RemoveQuotesTask instance. Returned instance is addRef-ed and
        must be released by a caller after usage.
        Caller code should initialize years - part of task
        
        NOTE: RemoveTask execution required write-lock type. It is not correct to start several Remove - tasks at the same time.
              IN this case any tasks may failed.   
     */
    virtual IRemoveQuotesTask* createRemoveQuotesTask(const char *instrument,
                                                      const char *timeframe,
                                                      IRemoveQuotesCallback *callback,
                                                      IError **error = 0) = 0;

    /** Executes a task.
        @param task
            the task
        @param error
            [out] error description
        @return
            true if task is taken for execution
            false if error occurred (see error 'param' for detail
     */
    virtual bool executeTask(Task *task, IError **error) = 0;

    /** Cancels execution of a task.
        Rules:
        - in general may be called from any thread except a notification thread;
        - only canceling of ReceiveTask is supported from a notification callback,
            other tasks may be canceled from other threads only;
        - before exiting calls one of onTask* callback. It may be called in 
            any thread context;
        - after cancelTask completed it's safe to destroy the object;
     */
    virtual void cancelTask(Task *task) = 0;


    /** Gets instruments supported by the quotes manager for specified price-stream.
        @return
          NULL - if error occurred
          empty collection if there is no instruments

     */
    virtual IInstruments* getInstruments(IError **error = 0) = 0;

    /** Gets timeframes supported by the quotes manager. 
        @return 
           collection with base timeframes (NULL is not allowed value)
    
     */
    virtual IBaseTimeframes* getBaseTimeframes() = 0;

    /** Gets size of data in the storage.
        Shows how many bytes the data for the specified instrument and year takes in bytes.
     */
    virtual int64 getDataSize(const char *instrument, const char *timeframe, int year, IError **error = 0) = 0;

    /** Sets storage limit
        By default storage is not limited.

        @param bytes
            new limit size in bytes
            if value <= 0 it reset current value and storage will works as unlimited storage
            If limit is less than min limit value it will not be applied
        @param error
            [out] error description
     */
    virtual void setStorageLimit(int64 bytes, IError **error) = 0;

    /** Gets storage limit
        @return
            storage limit in bytes
            -1 if storage unlimited
     */
    virtual int64 getStorageLimit(IError **error) const = 0;
 protected:
    virtual ~IQuotesManager() {}
};
} //~namespace quotesmgr
