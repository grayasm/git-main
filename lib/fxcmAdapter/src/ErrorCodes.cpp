/*
Copyright (C) 2017 Mihai Vasilian

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

contact: grayasm@gmail.com
*/


#include "ErrorCodes.hpp"
#include "exception.hpp"


namespace fxcm
{
	stl::string ErrorCodes::GetText(ErrorId id)
	{
		switch (id)
		{
		case ERR_SUCCESS: return "Success";
		case ERR_DISCONNECTED: return "Disconnected";
		case ERR_TIMEOUT: return "Timeout";		
		case ERR_NO_LOGIN_RULES: return "No login rules";
		case ERR_NO_ACOUNTS_RESPONSE: return "No accounts response";
		case ERR_NO_OFFERS_RESPONSE: return "No offers response";
		case ERR_NO_TRADES_RESPONSE: return "No trades response";
		case ERR_NO_RESPONSE_READER_FACTORY : return "No response reader factory";
		case ERR_NO_RESPONSE_READER: return "No response reader";
		case ERR_NO_PERMISSION_CHECKER: return "No permission checker";
		case ERR_NO_INSTRUMENT: return "No instrument";
		case ERR_NO_REQUEST_FACTORY: return "No request factory";
		case ERR_NO_ORDERS_REQUEST: return "No orders request";
		case ERR_NO_TRADES_REQUEST: return "No trades request";
		case ERR_NO_OFFER_AVAILABLE: return "No offer available";
		case ERR_TIMEFRAME_INCORRECT: return "Timeframe incorrect";
		case ERR_DATE_INTERVAL_INCORRECT: return "Date interval incorrect";
		case ERR_NO_MARKET_DATA_RESPONSE: return "No market data response";
		case ERR_NO_MARKET_DATA_READER: return "No market data reader";
		case ERR_NO_ACCOUNT: return "No account";

		default:
			throw stl::exception("Unknown ErrorId");
		} // switch
	}
} // namespace
