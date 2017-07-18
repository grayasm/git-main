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

#ifndef __LoginParams_hpp__
#define __LoginParams_hpp__

// c
// c++
// local
#include "autoptr.hpp"
#include "string.hpp"
#include "iniserv.hpp"


namespace fxcm
{
	class LoginParams
	{
	public:
		typedef misc::autoptr<fxcm::LoginParams> Ptr;

		LoginParams();
		LoginParams(const misc::string& inifile);
		~LoginParams();
		LoginParams(const LoginParams& tc);
		LoginParams& operator=(const LoginParams& tc);


		void SetLogin(const misc::string& user);
		const misc::string& GetLogin() const;

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

		void SetAccountSymbol(const misc::string& symbol);
		const misc::string& GetAccountSymbol() const;

		bool SaveIni();

	private:
		misc::string	m_iniFile;
		misc::string	m_section;
		misc::string	m_login;
		misc::string	m_pass;
		misc::string	m_url;
		misc::string	m_connection;
		misc::string	m_account;
		misc::string	m_sessionID;
		misc::string	m_pin;
		misc::string	m_accountSymbol;
	};
} // namespace



#endif // __LoginParams_hpp__
