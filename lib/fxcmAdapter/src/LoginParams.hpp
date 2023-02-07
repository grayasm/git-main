/*
Copyright (C) 2017 Mihai Vasilian
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
		typedef stl::autoptr<fxcm::LoginParams> Ptr;

		LoginParams();
		LoginParams(const stl::string& inifile);
		~LoginParams();
		LoginParams(const LoginParams& tc);
		LoginParams& operator=(const LoginParams& tc);


		void SetLogin(const stl::string& user);
		const stl::string& GetLogin() const;

		void SetPassword(const stl::string& pass);
		const stl::string& GetPassword() const;

		void SetUrl(const stl::string& url);
		const stl::string& GetUrl() const;

		void SetConnection(const stl::string& connection);
		const stl::string& GetConnection() const;

		void SetAccount(const stl::string& account);
		const stl::string& GetAccount() const;

		void SetSessionID(const stl::string& sessionID);
		const stl::string& GetSessionID() const;

		void SetPin(const stl::string& pin);
		const stl::string& GetPin() const;

		void SetAccountSymbol(const stl::string& symbol);
		const stl::string& GetAccountSymbol() const;

		bool SaveIni();

	private:
		stl::string	m_iniFile;
		stl::string	m_section;
		stl::string	m_login;
		stl::string	m_pass;
		stl::string	m_url;
		stl::string	m_connection;
		stl::string	m_account;
		stl::string	m_sessionID;
		stl::string	m_pin;
		stl::string	m_accountSymbol;
	};
} // namespace



#endif // __LoginParams_hpp__
