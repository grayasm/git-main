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
	
	extern misc::string	g_section;	// ("session");
	extern misc::string	g_login;	// ("user");
	extern misc::string	g_pass;		// ("password");
	extern misc::string	g_url;		// ("url");
	extern misc::string	g_connection;	// ("connection");
	extern misc::string	g_account;	// ("account");
	extern misc::string	g_sessionID;	// ("sessionID");
	extern misc::string	g_pin;		// ("pin");
	extern misc::string	g_currency;	// ("currency");
	

	IniParams::IniParams()
	{
	}

	IniParams::IniParams(const misc::string& inifile)
	{
		misc::iniserv iniReader(inifile);

		misc::string emptys("");

		m_iniFile = inifile;
		m_section = g_section;
		m_user = iniReader.get(m_section, g_login, emptys);
		m_pass = iniReader.get(m_section, g_pass, emptys);
		m_url = iniReader.get(m_section, g_url, emptys);
		m_connection = iniReader.get(m_section, g_connection, emptys);
		m_account = iniReader.get(m_section, g_account, emptys);
		m_sessionID = iniReader.get(m_section, g_sessionID, emptys);
		m_pin = iniReader.get(m_section, g_pin, emptys);
		m_currency = iniReader.get(m_section, g_currency, emptys);
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
			m_iniFile = tc.m_iniFile;
			m_section = tc.m_section;
			m_user = tc.m_user;
			m_pass = tc.m_pass;
			m_url = tc.m_url;
			m_connection = tc.m_connection;
			m_account = tc.m_account;
			m_sessionID = tc.m_sessionID;
			m_pin = tc.m_pin;
			m_currency = tc.m_currency;
		}
		return *this;
	}

	void IniParams::SetUser(const misc::string& user)
	{
		m_user = user;
	}

	const misc::string& IniParams::GetUser() const
	{
		return m_user;
	}

	void IniParams::SetPassword(const misc::string& pass)
	{
		m_pass = pass;
	}

	const misc::string& IniParams::GetPassword() const
	{
		return m_pass;
	}

	void IniParams::SetUrl(const misc::string& url)
	{
		m_url = url;
	}

	const misc::string& IniParams::GetUrl() const
	{
		return m_url;
	}

	void IniParams::SetConnection(const misc::string& connection)
	{
		m_connection = connection;
	}

	const misc::string& IniParams::GetConnection() const
	{
		return m_connection;
	}

	void IniParams::SetAccount(const misc::string& account)
	{
		m_account = account;
	}

	const misc::string& IniParams::GetAccount() const
	{
		return m_account;
	}

	void IniParams::SetSessionID(const misc::string& sessionID)
	{
		m_sessionID = sessionID;
	}

	const misc::string& IniParams::GetSessionID() const
	{
		return m_sessionID;
	}

	void IniParams::SetPin(const misc::string& pin)
	{
		m_pin = pin;
	}

	const misc::string& IniParams::GetPin() const
	{
		return m_pin;
	}

	void IniParams::SetAccountCurrency(const misc::string& symbol)
	{
		m_currency = symbol;
	}

	const misc::string& IniParams::GetAccountSymbol() const
	{
		return m_currency;
	}

	bool IniParams::SaveIni()
	{
		misc::iniserv iniWriter(m_iniFile);

		iniWriter.set(m_section, g_login, m_user);
		iniWriter.set(m_section, g_pass, m_pass);
		iniWriter.set(m_section, g_url, m_url);
		iniWriter.set(m_section, g_connection, m_connection);
		iniWriter.set(m_section, g_account, m_account);
		iniWriter.set(m_section, g_sessionID, m_sessionID);
		iniWriter.set(m_section, g_pin, m_pin);
		iniWriter.set(m_section, g_currency, m_currency);
		
		return iniWriter.write();
	}
} // namespace
