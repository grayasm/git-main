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

#include "fxcmIniParams.hpp"


namespace fxcm
{	
	misc::string	g_section("session");
	misc::string	g_user("user");
	misc::string	g_pass("password");
	misc::string	g_url("url");
	misc::string	g_connection("connection");
	misc::string	g_account("account");
	misc::string	g_sessionID("sessionID");
	misc::string	g_pin("pin");
	misc::string	g_currency("currency");
	misc::string	g_defval("");


	IniParams::IniParams()
	{
	}

	IniParams::IniParams(const misc::string& inifile)
	{
		m_inisrv = misc::iniserv(inifile);
	}

	IniParams::~IniParams()
	{		
	}

	IniParams::IniParams(const IniParams& tc)
	{
		*this = tc;
	}

	IniParams& IniParams::operator=(const IniParams& tc)
	{
		if(this != &tc)
		{
			m_inisrv = tc.m_inisrv;
		}
		return *this;
	}

	void IniParams::SetUser(const misc::string& user)
	{
		m_inisrv.set(g_section, g_user, user);
	}

	const misc::string& IniParams::GetUser() const
	{
		return m_inisrv.get(g_section, g_user, g_defval);
	}

	void IniParams::SetPassword(const misc::string& pass)
	{
		m_inisrv.set(g_section, g_pass, pass);
	}

	const misc::string& IniParams::GetPassword() const
	{
		return m_inisrv.get(g_section, g_pass, g_defval);
	}

	void IniParams::SetUrl(const misc::string& url)
	{
		m_inisrv.set(g_section, g_url, url);
	}

	const misc::string& IniParams::GetUrl() const
	{
		return m_inisrv.get(g_section, g_url, g_defval);
	}

	void IniParams::SetConnection(const misc::string& connection)
	{
		m_inisrv.set(g_section, g_connection, connection);
	}

	const misc::string& IniParams::GetConnection() const
	{
		return m_inisrv.get(g_section, g_connection, g_defval);
	}

	void IniParams::SetAccount(const misc::string& account)
	{
		m_inisrv.set(g_section, g_account, account);
	}

	const misc::string& IniParams::GetAccount() const
	{
		return m_inisrv.get(g_section, g_account, g_defval);
	}

	void IniParams::SetSessionID(const misc::string& sessionID)
	{
		m_inisrv.set(g_section, g_sessionID, sessionID);
	}

	const misc::string& IniParams::GetSessionID() const
	{
		return m_inisrv.get(g_section, g_sessionID, g_defval);
	}

	void IniParams::SetPin(const misc::string& pin)
	{
		m_inisrv.set(g_section, g_pin, pin);
	}

	const misc::string& IniParams::GetPin() const
	{
		return m_inisrv.get(g_section, g_pin, g_defval);
	}

	void IniParams::SetAccountCurrency(const misc::string& symbol)
	{
		m_inisrv.set(g_section, g_currency, symbol);
	}

	const misc::string& IniParams::GetAccountSymbol() const
	{
		return m_inisrv.get(g_section, g_currency, g_defval);
	}

	bool IniParams::SaveIni()
	{
		return m_inisrv.write();
	}
}; // namespace
