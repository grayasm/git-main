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

#ifndef __ErrorCodes_hpp__
#define __ErrorCodes_hpp__


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
			ERR_NO_RESPONSE_READER_FACTORY	= -105,
			ERR_NO_RESPONSE_READER = -106,
			ERR_NO_PERMISSION_CHECKER	= -107,
			ERR_NO_INSTRUMENT		= -108,
			ERR_NO_REQUEST_FACTORY	= -109,
			ERR_NO_ORDERS_REQUEST	= -110,
			ERR_NO_OFFER_AVAILABLE  = -111,
			ERR_TIMEFRAME_INCORRECT = -112,
			ERR_DATE_INTERVAL_INCORRECT = -113,
			ERR_NO_MARKET_DATA_RESPONSE = -114,
			ERR_NO_MARKET_DATA_READER = -115,
			ERR_NO_ACCOUNT = -116
		};

	public:
		ErrorCodes();
		~ErrorCodes();
		const char* GetText(ErrorId id) const;
	};
} // namespace

#endif // __ErrorCodes_hpp__
