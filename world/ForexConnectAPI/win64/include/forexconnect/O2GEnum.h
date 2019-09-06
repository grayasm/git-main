#pragma once

typedef enum
{
    TableUnknown = - 1,
    Offers = 0,
    Accounts = 1,
    Orders = 2,
    Trades = 3,
    ClosedTrades = 4,
    Messages = 5,
    Summary = 6
} O2GTable;

typedef enum
{
    ResponseUnknown = -1,
    TablesUpdates = 0,
    MarketDataSnapshot = 1,
    GetAccounts = 2,
    GetOffers = 3,
    GetOrders = 4,
    GetTrades = 5,
    GetClosedTrades = 6,
    GetMessages = 7,
    CreateOrderResponse = 8,
    GetSystemProperties = 9,
    CommandResponse = 10,
    MarginRequirementsResponse = 11,
    GetLastOrderUpdate = 12,
    MarketData = 13,
    Level2MarketData = 14,
} O2GResponseType;

typedef enum
{
    UpdateUnknown = - 1,
    Insert = 0,
    Update = 1,
    Delete = 2
} O2GTableUpdateType;

typedef enum
{
    PermissionDisabled = 0,
    PermissionEnabled = 1,
	PermissionUnknown = 2,
    PermissionHidden = -2
} O2GPermissionStatus;

typedef enum
{
    MarketStatusOpen = 0,     //!< Trading is allowed.
    MarketStatusClosed = 1,   //!< Trading is not allowed.
    MarketStatusUndefined = 2 //!< Undefined or unknown status
} O2GMarketStatus;

typedef enum
{
    Default = 0,
    NoPrice = 1
} O2GPriceUpdateMode;

typedef enum
{
    No = 0,
    Yes = 1
} O2GTableManagerMode;

typedef enum
{
    Initial = 0,     // initial status.
    Refreshing = 1,  // refresh in progress.
    Refreshed = 2,   // refresh is finished, table filled.
    Failed = 3       // refresh is failed.
} O2GTableStatus;

typedef enum
{
    ReportUrlOk = 0,
    ReportUrlNotSupported = -1,
    ReportUrlTooSmallBuffer = -2,
    ReportUrlNotLogged = -3,
    ReportUrlNoSession = -4,
    ReportUrlNoMemory = -5,
    ReportUrlSsoError = -6,
    ReportUrlNoAuthId = -7,
    ReportUrlNoSubId = -8,
    ReportUrlNoAccId = -9
} O2GReportUrlError;

typedef enum
{
    TokenOk = 0,
    TokenNotSupported = -1,
    TokenTooSmallBuffer = -2,
    TokenNotLogged = -3,
    TokenNoSession = -4,
    TokenSsoError = -5
} O2GTokenError;

typedef enum
{       
    TablesLoading = 0,
    TablesLoaded = 1,
    TablesLoadFailed = 2
} O2GTableManagerStatus;

typedef enum
{
    NoChartSession = 0,
    Attached = 1,
    Detached = 2
}
O2GChartSessionMode;

typedef enum       
{
    Between = -1,
    EqualTo = 0,
    NotEqualTo = 1,
    GreaterThan = 2,
    LessThan = 3,
    GreaterThanOrEqualTo = 4,
    LessThanOrEqualTo = 5
} O2GRelationalOperators;

typedef enum
{       
    OperatorAND = 0,
    OperatorOR = 1
} O2GLogicOperators;

typedef enum
{
    UnknownProcessStatus = -1,
    BeginTablesUpdate = 0,
    EndTablesUpdate = 1
} O2GUpdatesProcessStatus;

typedef enum
{
    AllEvents = 0,
    ServerOnly = 1
} O2GTableEventsFilter;

typedef enum
{
    PreviousClose = 0,
    FirstTick = 1
} O2GCandleOpenPriceMode;

typedef enum
{
    CommissionStageUnknown = -1,
    OpenCommission = 0,
    CloseCommission = 1,
    AnyDealCommission = 2
} O2GCommissionStage;

typedef enum 
{
    CommissionTypeUnknown = -1,
    CommissionPerLot = 0, 
    CommissionPerLotConv = 1, 
    CommissionPerTrade = 2,
    CommissionPerOrder = 3,
    CommissionPerOrderConv = 4,
    CommissionPerBasisPoints = 5,        
} O2GCommissionUnitType;

typedef enum
{
    CommissionStatusDisabled = 0,
    CommissionStatusLoading = 1,
    CommissionStatusReady = 2,
    CommissionStatusFailToLoad = 3
} O2GCommissionStatus;

typedef enum
{
	Undefined = 0,
	Trader = 20,
	Customer = 22,
	Dealer = 24,
	Admin = 26
} O2GUserKind;

typedef enum
{
    RolloverNotLoaded,
    RolloverLoading,
    RolloverReady,
    FailToLoad
} O2GRolloverStatus;

typedef enum
{
    RateNone = 0,
    RateNonPegged = 1,
    RatePeggedOpen = 2,
    RatePeggedClose = 3
} O2GRateType;

/** See system param SHOW_MR. */
typedef enum
{
	/* used when no SHOW_MR property received - default behavior */
	ShowUndefinedMR,
	ShowEMR,
	ShowMMR,
	ShowLMR,
	ShowAllMR,
} O2GShowMR;

typedef enum
{
    ContingencyTypeNo = 0,
    ContingencyTypeOCO = 1,
    ContingencyTypeOTO = 2,
    ContingencyTypeELS = 3,
    ContingencyTypeOTOCO = 4,
} O2GContingencyType;

/** Type of instrument. */
typedef enum
{
    InstrumentForex = 1,        //!< Regular forex instrument.
    InstrumentIndices = 2,      //!< Indices.
    InstrumentCommodity = 3,    //!< Commodities.
    InstrumentTreasury = 4,     //!< Treasuries.
    InstrumentBullion = 5,      //!< Bullion.
    InstrumentShares = 6,       //!< Shares.
    InstrumentFXIndex = 7,      //!< FXIndex.
    InstrumentCFDShares = 8,    //!< CFD Shares.
    InstrumentCrypto = 9        //!< Crypto.
} O2GInstrumentType;