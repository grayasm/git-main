#pragma once

#ifdef WIN32
    #define HIST_PRICE_API __declspec(dllimport)
#else
    #define HIST_PRICE_API
#endif

#include "ITimeframeFactory.h"
#include "IHistPriceAddRef.h"
#include "IHistPriceError.h"
#include "IPriceHistoryCommunicatorRequest.h"
#include "IPriceHistoryCommunicatorResponse.h"
#include "IPriceHistoryCommunicatorListener.h"
#include "IPriceHistoryCommunicatorStatusListener.h"
#include "IPriceHistoryCommunicator.h"
#include "PriceHistoryCommunicatorFactory.h"

#include "version.h"