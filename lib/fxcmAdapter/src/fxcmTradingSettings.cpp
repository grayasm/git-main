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


#include "fxcmTradingSettings.hpp"
#include "fxcmResponseListener.hpp"


namespace fxcm
{
	TradingSettings::TradingSettings()
	{
		Init();
	}

	TradingSettings::~TradingSettings()
	{
		Destroy();
	}

	TradingSettings::TradingSettings(const TradingSettings& tc)
	{
		*this = tc;
	}

	TradingSettings& TradingSettings::operator=(const TradingSettings& tc)
	{
		if(this != &tc)
		{
			m_symSettingsMap = tc.m_symSettingsMap;
			m_genSettings = tc.m_genSettings;
		}
		return *this;
	}

	bool TradingSettings::CheckTradingSettings(
		const fxcm::IniParams& iniParams,
		IO2GSession* session,
		misc::vector<misc::string>& symbols)
	{
		Clear();		

		// Pointers to generic data (loginRules, readerFactory, etc)
		O2G2Ptr<IO2GResponseReaderFactory> readerFactory = session->getResponseReaderFactory();
		if(!readerFactory)
		{
			misc::cout << "\n\tCannot create response reader factory";
			return false;
		}
		O2G2Ptr<IO2GLoginRules> loginRules = session->getLoginRules();
		if(!loginRules)
		{
			misc::cout << "\n\tCannot get login rules";
			return false;
		}


		// Identify the given account.		
		O2G2Ptr<IO2GResponse> accountsResponse = loginRules->getTableRefreshResponse(Accounts);
		if(!accountsResponse)
		{
			misc::cout << "\n\tCannot get response";
			return false;
		}
		O2G2Ptr<IO2GAccountsTableResponseReader> accountsReader = readerFactory->createAccountsTableReader(accountsResponse);
		O2G2Ptr<IO2GAccountRow> account = NULL;
		for(int i=0; i < accountsReader->size(); ++i)
		{
			O2G2Ptr<IO2GAccountRow> acc2 = accountsReader->getRow(i);
			if(acc2)
			{
				const char* accountID = acc2->getAccountID();		// 2475538
				const char* accountKind = acc2->getAccountKind();	// 32

				if(iniParams.GetAccount() == accountID)
				{
					if( strcmp(acc2->getMarginCallFlag(), "N") == 0 &&
						(strcmp(accountKind, "32") == 0 || strcmp(accountKind, "36") == 0 ))
					{
						account = acc2;
						break;
					}
				}
			}
		}

		if(!account)
		{
			misc::cout << "\n\tCannot find account";
			return false;
		}

		// Acquire instruments subscription table.
		O2G2Ptr<IO2GResponse> offersResponse = loginRules->getTableRefreshResponse(Offers);
		if(!offersResponse)
		{
			misc::cout << "\n\tCannot get the offers table.";
			return false;
		}
		O2G2Ptr<IO2GOffersTableResponseReader> offersReader = readerFactory->createOffersTableReader(offersResponse);
		
		ResponseListener dummyListener;

		// Retrieve all instruments and specific settings.
		O2G2Ptr<IO2GTradingSettingsProvider> tradingSettingsProvider = loginRules->getTradingSettingsProvider();	
		
		for(int i=0; i < offersReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> offer = offersReader->getRow(i);

			if(!dummyListener.IsOfferTradable(offer))
				continue;

			if(!dummyListener.IsOfferValid(offer))
				continue;

			const char* sInstrument = offer->getInstrument();

			SymbolSettings symbolSettings;			
			symbolSettings.m_condDistStopForTrade = tradingSettingsProvider->getCondDistStopForTrade(sInstrument);
			symbolSettings.m_condDistLimitForTrade = tradingSettingsProvider->getCondDistLimitForTrade(sInstrument);
			symbolSettings.m_condDistEntryStop = tradingSettingsProvider->getCondDistEntryStop(sInstrument);
			symbolSettings.m_condDistEntryLimit = tradingSettingsProvider->getCondDistEntryLimit(sInstrument);
			symbolSettings.m_minQuantity = tradingSettingsProvider->getMinQuantity(sInstrument, account);
			symbolSettings.m_maxQuantity = tradingSettingsProvider->getMaxQuantity(sInstrument, account);
			symbolSettings.m_baseUnitSize = tradingSettingsProvider->getBaseUnitSize(sInstrument, account);
			symbolSettings.m_marketStatus = tradingSettingsProvider->getMarketStatus(sInstrument);
			symbolSettings.m_MMR = tradingSettingsProvider->getMMR(sInstrument, account);
			symbolSettings.m_ThreeLM = tradingSettingsProvider->getMargins(sInstrument, account, symbolSettings.m_MMR2, symbolSettings.m_EMR, symbolSettings.m_LMR);

			m_symSettingsMap[sInstrument] = symbolSettings;
			symbols.push_back(sInstrument);
		}

		m_genSettings.m_minTrailingStep = tradingSettingsProvider->getMinTrailingStep();
		m_genSettings.m_maxTrailingStep = tradingSettingsProvider->getMaxTrailingStep();		
		
		return true;
	}

	void TradingSettings::Clear()
	{
		Init();
	}

	const SymbolSettings& TradingSettings::GetTradingSettings(const misc::string& symbol) const
	{
		std::map<misc::string, SymbolSettings>::const_iterator it = m_symSettingsMap.find(symbol);
		if(it == m_symSettingsMap.end())
			throw misc::exception("Invalid symbol");
		return it->second;
	}

	const GeneralSettings& TradingSettings::GetTradingSettings() const
	{
		if(m_symSettingsMap.empty())
			throw misc::exception("Invalid settings");
		return m_genSettings;
	}

	void TradingSettings::Init()
	{
		m_symSettingsMap.clear();
		m_genSettings.m_maxTrailingStep = 0;
		m_genSettings.m_minTrailingStep = 0;
	}

	void TradingSettings::Destroy()
	{
		Init();
	}
} // namespace fxcm

