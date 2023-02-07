/*
Copyright (C) 2017 Mihai Vasilian
*/

#ifndef __ErrorCodes_hpp__
#define __ErrorCodes_hpp__

#include "string.hpp"

namespace fxcm
{
	class ErrorCodes
	{
	public:
		enum ErrorId
		{
			ERR_SUCCESS				= 0,
			ERR_DISCONNECTED		= -100,
			ERR_TIMEOUT				= -101,
			ERR_NO_LOGIN_RULES		= -102,
			ERR_NO_ACOUNTS_RESPONSE = -103,
			ERR_NO_OFFERS_RESPONSE	= -104,
			ERR_NO_TRADES_RESPONSE	= -105,
			ERR_NO_RESPONSE_READER_FACTORY	= -106,
			ERR_NO_RESPONSE_READER = -107,
			ERR_NO_PERMISSION_CHECKER	= -108,
			ERR_NO_INSTRUMENT		= -109,
			ERR_NO_REQUEST_FACTORY	= -110,
			ERR_NO_ORDERS_REQUEST	= -111,
			ERR_NO_TRADES_REQUEST	= -112,
			ERR_NO_OFFER_AVAILABLE  = -113,
			ERR_TIMEFRAME_INCORRECT = -114,
			ERR_DATE_INTERVAL_INCORRECT = -115,
			ERR_NO_MARKET_DATA_RESPONSE = -116,
			ERR_NO_MARKET_DATA_READER = -117,
			ERR_NO_ACCOUNT = -118
		};

		static stl::string GetText(ErrorId id);
	
	private:
		// abstract class
		ErrorCodes();
		~ErrorCodes();
	};
} // namespace

#endif // __ErrorCodes_hpp__
