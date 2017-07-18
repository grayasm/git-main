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



#include "LoginParams.hpp"


namespace fxcm
{
	misc::string	g_section("session");
	misc::string	g_login("login");
	misc::string	g_pass("password");
	misc::string	g_url("url");
	misc::string	g_connection("connection");
	misc::string	g_account("account");
	misc::string	g_sessionID("sessionID");
	misc::string	g_pin("pin");
	misc::string	g_currency("accountSymbol");


	LoginParams::LoginParams()
	{
	}

	LoginParams::LoginParams(const misc::string& inifile)
	{
		misc::iniserv iniReader(inifile);

		misc::string emptys("");

		m_iniFile = inifile;
		m_section = g_section;
		m_login = iniReader.get(m_section, g_login, emptys);
		m_pass = iniReader.get(m_section, g_pass, emptys);
		m_url = iniReader.get(m_section, g_url, emptys);
		m_connection = iniReader.get(m_section, g_connection, emptys);
		m_account = iniReader.get(m_section, g_account, emptys);
		m_sessionID = iniReader.get(m_section, g_sessionID, emptys);
		m_pin = iniReader.get(m_section, g_pin, emptys);
		m_accountSymbol = iniReader.get(m_section, g_currency, emptys);
	}

	LoginParams::~LoginParams()
	{
	}

	LoginParams::LoginParams(const LoginParams& tc)
	{
		*this = tc;
	}

	LoginParams& LoginParams::operator=(const LoginParams& tc)
	{
		if (this != &tc)
		{
			m_iniFile = tc.m_iniFile;
			m_section = tc.m_section;
			m_login = tc.m_login;
			m_pass = tc.m_pass;
			m_url = tc.m_url;
			m_connection = tc.m_connection;
			m_account = tc.m_account;
			m_sessionID = tc.m_sessionID;
			m_pin = tc.m_pin;
			m_accountSymbol = tc.m_accountSymbol;
		}
		return *this;
	}

	void LoginParams::SetLogin(const misc::string& login)
	{
		m_login = login;
	}

	const misc::string& LoginParams::GetLogin() const
	{
		return m_login;
	}

	void LoginParams::SetPassword(const misc::string& pass)
	{
		m_pass = pass;
	}

	const misc::string& LoginParams::GetPassword() const
	{
		return m_pass;
	}

	void LoginParams::SetUrl(const misc::string& url)
	{
		m_url = url;
	}

	const misc::string& LoginParams::GetUrl() const
	{
		return m_url;
	}

	void LoginParams::SetConnection(const misc::string& connection)
	{
		m_connection = connection;
	}

	const misc::string& LoginParams::GetConnection() const
	{
		return m_connection;
	}

	void LoginParams::SetAccount(const misc::string& account)
	{
		m_account = account;
	}

	const misc::string& LoginParams::GetAccount() const
	{
		return m_account;
	}

	void LoginParams::SetSessionID(const misc::string& sessionID)
	{
		m_sessionID = sessionID;
	}

	const misc::string& LoginParams::GetSessionID() const
	{
		return m_sessionID;
	}

	void LoginParams::SetPin(const misc::string& pin)
	{
		m_pin = pin;
	}

	const misc::string& LoginParams::GetPin() const
	{
		return m_pin;
	}

	void LoginParams::SetAccountSymbol(const misc::string& symbol)
	{
		m_accountSymbol = symbol;
	}

	const misc::string& LoginParams::GetAccountSymbol() const
	{
		return m_accountSymbol;
	}

	bool LoginParams::SaveIni()
	{
		misc::iniserv iniWriter(m_iniFile);

		iniWriter.set(m_section, g_login, m_login);
		iniWriter.set(m_section, g_pass, m_pass);
		iniWriter.set(m_section, g_url, m_url);
		iniWriter.set(m_section, g_connection, m_connection);
		iniWriter.set(m_section, g_account, m_account);
		iniWriter.set(m_section, g_sessionID, m_sessionID);
		iniWriter.set(m_section, g_pin, m_pin);
		iniWriter.set(m_section, g_currency, m_accountSymbol);

		return iniWriter.write();
	}
} // namespace


