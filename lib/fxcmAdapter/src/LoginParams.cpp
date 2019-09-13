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
	stl::string	g_section("session");
	stl::string	g_login("login");
	stl::string	g_pass("password");
	stl::string	g_url("url");
	stl::string	g_connection("connection");
	stl::string	g_account("account");
	stl::string	g_sessionID("sessionID");
	stl::string	g_pin("pin");
	stl::string	g_currency("accountSymbol");


	LoginParams::LoginParams()
	{
	}

	LoginParams::LoginParams(const stl::string& inifile)
	{
		misc::iniserv iniReader(inifile);

		stl::string emptys("");

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

	void LoginParams::SetLogin(const stl::string& login)
	{
		m_login = login;
	}

	const stl::string& LoginParams::GetLogin() const
	{
		return m_login;
	}

	void LoginParams::SetPassword(const stl::string& pass)
	{
		m_pass = pass;
	}

	const stl::string& LoginParams::GetPassword() const
	{
		return m_pass;
	}

	void LoginParams::SetUrl(const stl::string& url)
	{
		m_url = url;
	}

	const stl::string& LoginParams::GetUrl() const
	{
		return m_url;
	}

	void LoginParams::SetConnection(const stl::string& connection)
	{
		m_connection = connection;
	}

	const stl::string& LoginParams::GetConnection() const
	{
		return m_connection;
	}

	void LoginParams::SetAccount(const stl::string& account)
	{
		m_account = account;
	}

	const stl::string& LoginParams::GetAccount() const
	{
		return m_account;
	}

	void LoginParams::SetSessionID(const stl::string& sessionID)
	{
		m_sessionID = sessionID;
	}

	const stl::string& LoginParams::GetSessionID() const
	{
		return m_sessionID;
	}

	void LoginParams::SetPin(const stl::string& pin)
	{
		m_pin = pin;
	}

	const stl::string& LoginParams::GetPin() const
	{
		return m_pin;
	}

	void LoginParams::SetAccountSymbol(const stl::string& symbol)
	{
		m_accountSymbol = symbol;
	}

	const stl::string& LoginParams::GetAccountSymbol() const
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


