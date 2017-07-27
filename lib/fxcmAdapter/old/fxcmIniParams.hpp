/*
  Copyright (C) 2014 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
*/


#ifndef __fxcmIniParams_hpp__
#define __fxcmIniParams_hpp__

// c
// c++
// local
#include "autoptr.hpp"
#include "string.hpp"
#include "iniserv.hpp"


namespace fxcm
{
	class IniParams
	{
	public:
		typedef misc::autoptr<fxcm::IniParams> Ptr;

		IniParams();
		IniParams(const misc::string& inifile);
		~IniParams();
		IniParams(const IniParams& tc);
		IniParams& operator=(const IniParams& tc);

				
		void SetUser(const misc::string& user);
		const misc::string& GetUser() const;

		void SetPassword(const misc::string& pass);
		const misc::string& GetPassword() const;

		void SetUrl(const misc::string& url);
		const misc::string& GetUrl() const;

		void SetConnection(const misc::string& connection);
		const misc::string& GetConnection() const;

		void SetAccount(const misc::string& account);
		const misc::string& GetAccount() const;

		void SetSessionID(const misc::string& sessionID);
		const misc::string& GetSessionID() const;

		void SetPin(const misc::string& pin);
		const misc::string& GetPin() const;

		void SetAccountCurrency(const misc::string& symbol);
		const misc::string& GetAccountSymbol() const;

		bool SaveIni();
	
	private:
		misc::string	m_iniFile;
		misc::string	m_section;
		misc::string	m_user;
		misc::string	m_pass;
		misc::string	m_url;
		misc::string	m_connection;
		misc::string	m_account;
		misc::string	m_sessionID;
		misc::string	m_pin;
		misc::string	m_currency;
	};
} // namespace

#endif // __fxcmIniParams_hpp__

