
#ifdef WIN32
    #define QUOTESMGR2_API __declspec(dllimport)
    #define QUOTESMGR2_IMPL
#else
    #define QUOTESMGR2_API
    #define QUOTESMGR2_IMPL
#endif

#include "IAddRef.h"
#include "quotes_mgr.h"
#include "IError.h"
#include "IString.h"
#include "IStringsLoader.h"
#include "candleperiod.h"
#include "version.h"
