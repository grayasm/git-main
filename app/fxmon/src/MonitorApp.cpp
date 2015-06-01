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

#include <float.h>
#include <math.h>
#include "unistd.hpp"
#include "strconv.hpp"
#include "MonitorApp.hpp"
#include "Deserializer.hpp"
#include "MarketPlugin.hpp"
#include "MonConsoleHandlerPlugin.hpp"
#include "MonQuoteUpdateTimeoutPlugin.hpp"




misc::string g_monitorIni("monitor.ini");
misc::string g_trading   ("trading.txt");

MonitorApp::MonitorApp()
{		
	m_monitorIni = MonitorIni(g_monitorIni);
	m_sessionIni = fxcm::IniParams(g_monitorIni);
	m_session = new MonSession();
	m_engine = new MonEngine();

	if(!Create())
	{
		// failed; turn off execution
		m_engine = 0;
		m_session = 0;
	}
}


MonitorApp::~MonitorApp()
{	
}

bool MonitorApp::Menu()
{
	if(m_engine.IsNull())
		return false;

	do 
	{
		ShowMenu();
	}
	while(ProcessOption());

	return true;
}

bool MonitorApp::Create()
{
	// --- Create session ---
	if(!m_session->CreateSession(m_monitorIni, m_sessionIni))
		return false;
	m_engine->SetSession(m_session);

	// --- Set parameters ---
	m_engine->SetIniParams(m_monitorIni);

	// --- Register plugins ---
	MonConsoleHandlerPlugin::Ptr consolePlugin = new MonConsoleHandlerPlugin();
	consolePlugin->SetEngine(&*m_engine);
	m_engine->Register(consolePlugin);

	MonQuoteUpdateTimeoutPlugin::Ptr timeoutPlugin = new MonQuoteUpdateTimeoutPlugin();
	timeoutPlugin->SetTimeOut(m_monitorIni.GetQuoteUpdateTimeout());
	m_engine->Register(timeoutPlugin);

	return true;
}

bool MonitorApp::Run()
{	
	// --- Add strategies ---
	for(size_t i = 0; i < m_deserialized_strategies.size(); ++i)
	{
		const fx::StrategyBase::Ptr& s = m_deserialized_strategies[i];
		m_engine->Add(s);
	}

	for(size_t i = 0; i < m_new_strategies.size(); ++i)
	{
		const fx::StrategyBase::Ptr& s = m_new_strategies[i];
		m_engine->Add(s);
	}

	// --- Start engine ---
	return m_engine->Start();
}

void MonitorApp::ShowMenu()
{
	clrscr();
	misc::cout << "\n-----------------------------------------------------------";
	misc::cout << "\nconnection     : " << m_monitorIni.GetConnection().c_str();
	misc::cout << "\nmarket plugin  : " << m_monitorIni.GetMarketPlugin().c_str();
	misc::cout << "\nupdate timeout : " << m_monitorIni.GetQuoteUpdateTimeout();
	misc::cout << "\nsession        : " << (m_session.IsNotNull() == true ? "valid" : "invalid");
	misc::cout << "\nengine         : " << (m_engine.IsNotNull() == true ? "ready" : "off");
	misc::cout << "\n-----------------------------------------------------------";
	misc::cout << "\n";
	misc::cout << "\ndeserialize strategies       (d/D) [in the market now]";
	misc::cout << "\nlist deserialized strategies (l/L) [in the market now]";
	misc::cout << "\ncreate new strategy          (c/C)";
	misc::cout << "\nshow new strategies          (s/S)";
	misc::cout << "\nerase new strategy           (e/E)";
	misc::cout << "\n-----------------------------------------------------------";
	misc::cout << "\nstart engine (r/R)";
	misc::cout << "\nexit         (q/Q)";
	misc::cout << "\n-----------------------------------------------------------";
	misc::cout << "\noption= ";
}

bool MonitorApp::ProcessOption()
{
	std::string stdline;
	std::getline(misc::cin, stdline);

	if(misc::cin.fail())
		// CTRL-C pressed
		return false;

	if(stdline.empty())
	{
		misc::cout << "\nempty option, retry in 2 sec";
		sleep(2);
		return true;
	}

	char key = stdline[0];

	if(key == 'd' || key == 'D')
	{
		Deserialize();
	}
	else if(key == 'l' || key == 'L')
	{
		ListDeserialized();		
	}
	else if(key == 'c' || key == 'C')
	{
		CreateNewStrategy();
	}
	else if(key == 's' || key == 'S')
	{
		ShowNewStrategies();
	}
	else if(key == 'e' || key == 'E')
	{
		EraseNewStrategy();
	}
	else if(key == 'r' || key == 'R')
	{
		Run();
		// engine stopped
		return false;
	}
	else if(key == 'q' || key == 'Q')
	{
		misc::cout << "\nConfirm exit [q/Q] = ";
		if(ConfirmOption('q', 'Q'))
			return false;
	}

	return true;
}

bool MonitorApp::ConfirmOption(char key, char KEY)
{
	std::string stdline;
	std::getline(misc::cin, stdline);
	if(stdline.empty())
		return false;
	return (stdline[0] == key || stdline[0] == KEY);
}

bool MonitorApp::GetOption(misc::string& val)
{
	val.clear();
	std::string stdline;
	std::getline(misc::cin, stdline);
	if(stdline.empty())
		return false;
	val = stdline.c_str();
	misc::trim(val);
	return true;
}

void MonitorApp::Deserialize()
{
	m_deserialized_strategies.clear();
	fx::Deserializer ds(g_trading);
	fx::MarketPlugin::Ptr plugin = m_session->GetMarketPlugin();
	ds.SetPlugin(plugin);
	ds.Deserialize();
	const Strategies& strategies = ds.GetData();
	for(size_t i = 0; i < strategies.size(); ++i)
	{
		m_deserialized_strategies.push_back(strategies[i]);
	}

	misc::cout << "\nDeserialized " << m_deserialized_strategies.size() << " strategies.";
	ConfirmOption('y', 'Y'); // stop after listing
}

void MonitorApp::ListDeserialized()
{
	StrategyOutputVisitor visitor(std::cout);
	for(size_t i = 0; i < m_deserialized_strategies.size(); ++i)
	{
		misc::cout << "\n";
		fx::StrategyBase::Ptr s = m_deserialized_strategies[i];
		s->AcceptVisitor(visitor);
	}
	
	if(m_deserialized_strategies.empty())
		misc::cout << "\n0 strategies deserialized.";
	ConfirmOption('y', 'Y'); // stop after listing
}

void MonitorApp::CreateNewStrategy()
{
	misc::cout << "\n";
	misc::cout << "\ncreate Hedge Fix Grid        (a)";
	misc::cout << "\ncreate Hedge Fix Grid * Grid (b)";
	misc::cout << "\ncreate Double Hedge Fix Grid (c)";
	misc::cout << "\ncreate Fix Grid              (d)";
	misc::cout << "\ncreate Double Fix Grid       (e)";
	misc::cout << "\noption = ";
	misc::string val;
	GetOption(val);
	if(val.empty())
	{
		misc::cout << "\nempty option, wait 2 seconds";
		sleep(2);
		return ;
	}
	
	if(val[0] == 'a' || val[0] == 'A')
		return CreateNewHFGStrategy();

	if(val[0] == 'b' || val[0] == 'B')
		return CreateNewHFGStrategies();

	if(val[0] == 'c' || val[0] == 'C')
		return CreateNew2HFGStrategy();

	if(val[0] == 'd' || val[0] == 'D')
		return CreateNewFGStrategy();

	if(val[0] == 'e' || val[0] == 'E')
		return CreateNew2FGStrategy();

	misc::cout << "\ninvalid option, wait 2 seconds";
	sleep(2);	
}

void MonitorApp::CreateNewHFGStrategy()
{
	std::map<misc::string, fx::Price> quotes;
	if(!m_session->GetOffer(quotes))
	{
		misc::cout << "\nCannot retrieve market offer.";
		ConfirmOption('y', 'y'); // stop after message
	}

	if(quotes.find("EUR/USD") == quotes.end())
	{
		misc::cout << "\nInstrument 'EUR/USD' invalid.";
		ConfirmOption('y', 'y'); // stop after message
		return;
	}

	
	// market entry level
	fx::Price price = quotes["EUR/USD"];	
	fx::Currency currency("EUR/USD", price, 5, 0.08, 10000);
	fx::Position ep;
	bool isBuy = false;
	double amount = 0;
	// strategy
	bool wait = false;
	double dh = 0;
	double dg = 0;
	double ha = 0;
	double de = 0;
	double maxn = 0;
	double maxp = 0;
	fx::MarketPlugin::Ptr plugin = m_session->GetMarketPlugin();

	misc::string val;

	misc::cout << "\nCreate a new Hedge Fix Grid strategy";
	misc::cout << "\nInstrument       = " << currency.GetSymbol().c_str();
	misc::cout << "\nBuy [y/Y]        = "; isBuy = ConfirmOption('y', 'Y');
	misc::cout << "\nAmount (k)       = "; GetOption(val); misc::to_value(val, amount);
	misc::cout << "\nPrice            = " << 
		" B: " << misc::from_value(price.GetBuy(), 5) <<
		" S: " << misc::from_value(price.GetSell(), 5);

	misc::cout << "\nWant to enter at different price y/N = ";
	if(ConfirmOption('y', 'Y'))
	{
		wait = true;
		misc::cout << "\nOpen price = "; GetOption(val);
		double open = 0;
		misc::to_value(val, open);
		double pdiff = fabs(open - price.GetBuy()) * currency.GetRate2Pip();
		if(pdiff > 100)
		{
			misc::cout << "\nPrice rejected as too far from current level.";
			GetOption(val); // stop after message
			return;
		}
		price = fx::Price(open, open);
		currency = fx::Currency("EUR/USD", price, 5, 0.08, 10000);
	}

	double commission = 0;
	double interest = 0;

	ep = fx::Position("", "", currency, isBuy, amount, commission, interest);

	misc::cout << "\ndist to hedge(dh)= "; GetOption(val); misc::to_value(val, dh);
	misc::cout << "\ndist of grid (dg)= "; GetOption(val); misc::to_value(val, dg);
	misc::cout << "\nhedge amount (ha)= "; GetOption(val); misc::to_value(val, ha);
	misc::cout << "\ndist to exit (de)= "; GetOption(val); misc::to_value(val, de);
	misc::cout << "\nmax negative (mn)= "; GetOption(val); misc::to_value(val, maxn);
	misc::cout << "\nmax positive (mp)= "; GetOption(val); misc::to_value(val, maxp);


	fx::StrategyHedgeFixGrid::Ptr hfg = 
		new fx::StrategyHedgeFixGrid(ep, wait, dh, dg, ha, de, maxn, maxp, plugin);

	m_new_strategies.push_back(hfg);
}

void MonitorApp::CreateNewHFGStrategies()
{
	std::map<misc::string, fx::Price> quotes;
	if(!m_session->GetOffer(quotes))
	{
		misc::cout << "\nCannot retrieve market offer.";
		ConfirmOption('y', 'y'); // stop after message
	}

	if(quotes.find("EUR/USD") == quotes.end())
	{
		misc::cout << "\nInstrument 'EUR/USD' invalid.";
		ConfirmOption('y', 'y'); // stop after message
		return;
	}


	// market entry level
	fx::Price price = quotes["EUR/USD"];	
	fx::Currency currency("EUR/USD", price, 5, 0.08, 10000);
	fx::Position ep;
	bool isBuy = false;
	double amount = 0;
	// strategy

	/* All hedge fix grid entries will be in a grid
	 * at equal distance.
	 */
	bool wait = true;
	double dh = 0;
	double dg = 0;
	double ha = 0;
	double de = 0;
	double maxn = 0;
	double maxp = 0;
	fx::MarketPlugin::Ptr plugin = m_session->GetMarketPlugin();

	misc::string val;

	misc::cout << "\nCreate new Hedge Fix Grid  **Strategies**";
	misc::cout << "\nInstrument       = " << currency.GetSymbol().c_str();
	misc::cout << "\nBuy [y/Y]        = "; isBuy = ConfirmOption('y', 'Y');
	misc::cout << "\nAmount (k)       = "; GetOption(val); misc::to_value(val, amount);
	misc::cout << "\nMarket price now = " << 
		" B: " << misc::from_value(price.GetBuy(), 5) <<
		" S: " << misc::from_value(price.GetSell(), 5);


	misc::cout << "\nYou need to introduce only the price where the first";
	misc::cout << "\nstrategy will be added to market.";
	misc::cout << "\nAll consecutive delayed entries will be established based on that.";

	wait = true;
	misc::cout << "\nOpen price = "; GetOption(val);
	double open = 0;
	misc::to_value(val, open);
	double pdiff = fabs(open - price.GetBuy()) * currency.GetRate2Pip();
	if(pdiff > 200)
	{		
		misc::cout << "\nPrice rejected as too far from current level. 200 pl maxim accepted";
		GetOption(val); // stop after message
		return;
	}
	
	misc::cout << "\ndist to hedge(dh)= "; GetOption(val); misc::to_value(val, dh);
	misc::cout << "\ndist of grid (dg)= "; GetOption(val); misc::to_value(val, dg);
	misc::cout << "\nhedge amount (ha)= "; GetOption(val); misc::to_value(val, ha);
	misc::cout << "\ndist to exit (de)= "; GetOption(val); misc::to_value(val, de);
	misc::cout << "\nmax negative (mn)= "; GetOption(val); misc::to_value(val, maxn);
	misc::cout << "\nmax positive (mp)= "; GetOption(val); misc::to_value(val, maxp);

	double commission = 0;
	double interest = 0;

	double griddist = 0;
	misc::cout << "\nGRID: Value of pips between positions can be:";
	misc::cout << "\nGRID: negative - grid descending";
	misc::cout << "\nGRID: positive - grid ascending";
	misc::cout << "\nGRID: Pips between positions = "; GetOption(val); misc::to_value(val, griddist);
	if(fabs(griddist) > 10)
	{
		misc::cout << "\nGrid distance rejected as too big. 10 pl maxim accepted";
		GetOption(val); // stop after message
		return;
	}

	size_t gridcount = 0;
	misc::cout << "\nGRID: How many entries do you need = "; GetOption(val); misc::to_value(val, gridcount);
	if(gridcount > 20)
	{
		misc::cout << "\nGrid count rejected as too big. 20 entries maxim accepted";
		GetOption(val); // stop after message
		return;
	}

	misc::cout << "\nGRID: Printing ...";

	Strategies grid_strategies;
	for(size_t i = 0; i < gridcount; ++i)
	{
		//TODO: hard coded values for "EUR/USD"
		double pips2rate = 1. / 10000.;
		double add2price = griddist * i * pips2rate;
		price = fx::Price(open + add2price, open + add2price);
		currency = fx::Currency("EUR/USD", price, 5, 0.08, 10000);
		ep = fx::Position("", "", currency, isBuy, amount, commission, interest);

		fx::StrategyHedgeFixGrid::Ptr hfg = 
			new fx::StrategyHedgeFixGrid(ep, wait, dh, dg, ha, de, maxn, maxp, plugin);

		grid_strategies.push_back(hfg);
		misc::cout << "\n" << i << hfg->ToString();
	}
	
	misc::cout << "\n\nDo you accept the GRID [y/N] = ";
	if(ConfirmOption('y', 'Y'))
	{
		for(size_t i = 0; i < grid_strategies.size(); ++i)
			m_new_strategies.push_back( grid_strategies[i] );
	}	
}

void MonitorApp::CreateNew2HFGStrategy()
{
	std::map<misc::string, fx::Price> quotes;
	if(!m_session->GetOffer(quotes))
	{
		misc::cout << "\nCannot retrieve market offer.";
		ConfirmOption('y', 'y'); // stop after message
	}

	if(quotes.find("EUR/USD") == quotes.end())
	{
		misc::cout << "\nInstrument 'EUR/USD' invalid.";
		ConfirmOption('y', 'y'); // stop after message
		return;
	}


	// market entry level
	fx::Price price = quotes["EUR/USD"];	
	fx::Currency currency("EUR/USD", price, 5, 0.08, 10000);
	fx::Position ep;
	bool isBuy = false;
	double amount = 0;
	// strategy
	bool wait = false;
	double dh = 0;
	double dg = 0;
	double ha = 0;
	double de = 0;
	double maxn = 0;
	double maxp = 0;
	fx::MarketPlugin::Ptr plugin = m_session->GetMarketPlugin();

	misc::string val;

	misc::cout << "\nCreate a new 2(Double) Hedge Fix Grid strategy";
	misc::cout << "\nInstrument       = " << currency.GetSymbol().c_str();
	misc::cout << "\nBuy/Sell ? I choose !"; isBuy = true;
	misc::cout << "\nAmount (k)       = "; GetOption(val); misc::to_value(val, amount);
	misc::cout << "\nPrice            = " << 
		" B: " << misc::from_value(price.GetBuy(), 5) <<
		" S: " << misc::from_value(price.GetSell(), 5);

	misc::cout << "\nWant to enter at different price y/N = ";
	if(ConfirmOption('y', 'Y'))
	{
		wait = true;
		misc::cout << "\nOpen price = "; GetOption(val);
		double open = 0;
		misc::to_value(val, open);
		double pdiff = fabs(open - price.GetBuy()) * currency.GetRate2Pip();
		if(pdiff > 100)
		{
			misc::cout << "\nPrice rejected as too far from current level.";
			GetOption(val); // stop after message
			return;
		}
		price = fx::Price(open, open);
		currency = fx::Currency("EUR/USD", price, 5, 0.08, 10000);
	}

	double commission = 0;
	double interest = 0;

	ep = fx::Position("", "", currency, isBuy, amount, commission, interest);

	misc::cout << "\ndist to hedge(dh)= "; GetOption(val); misc::to_value(val, dh);
	misc::cout << "\ndist of grid (dg)= "; GetOption(val); misc::to_value(val, dg);
	misc::cout << "\nhedge amount (ha)= "; GetOption(val); misc::to_value(val, ha);
	misc::cout << "\ndist to exit (de)= "; GetOption(val); misc::to_value(val, de);
	misc::cout << "\nmax negative (mn)= "; GetOption(val); misc::to_value(val, maxn);
	misc::cout << "\nmax positive (mp)= "; GetOption(val); misc::to_value(val, maxp);


	fx::Strategy2HedgeFixGrid::Ptr hfg = 
		new fx::Strategy2HedgeFixGrid(ep, wait, dh, dg, ha, de, maxn, maxp, plugin);

	m_new_strategies.push_back(hfg);
}

void MonitorApp::CreateNewFGStrategy()
{
	std::map<misc::string, fx::Price> quotes;
	if(!m_session->GetOffer(quotes))
	{
		misc::cout << "\nCannot retrieve market offer.";
		ConfirmOption('y', 'y'); // stop after message
	}

	if(quotes.find("EUR/USD") == quotes.end())
	{
		misc::cout << "\nInstrument 'EUR/USD' invalid.";
		ConfirmOption('y', 'y'); // stop after message
		return;
	}


	// market entry level
	fx::Price price = quotes["EUR/USD"];	
	fx::Currency currency("EUR/USD", price, 5, 0.08, 10000);
	fx::Position ep;
	bool isBuy = false;
	double amount = 0;
	// strategy
	bool wait = false;
	double dg = 0;
	double pa = 0;
	double de = 0;
	double maxn = 0;
	double maxp = 0;
	fx::MarketPlugin::Ptr plugin = m_session->GetMarketPlugin();

	misc::string val;

	misc::cout << "\nCreate a new Fix Grid strategy";
	misc::cout << "\nInstrument       = " << currency.GetSymbol().c_str();
	misc::cout << "\nBuy [y/Y]        = "; isBuy = ConfirmOption('y', 'Y');
	misc::cout << "\nAmount (k)       = "; GetOption(val); misc::to_value(val, amount);
	misc::cout << "\nPrice            = " << 
		" B: " << misc::from_value(price.GetBuy(), 5) <<
		" S: " << misc::from_value(price.GetSell(), 5);

	misc::cout << "\nWant to enter at different price y/N = ";
	if(ConfirmOption('y', 'Y'))
	{
		wait = true;
		misc::cout << "\nOpen price = "; GetOption(val);
		double open = 0;
		misc::to_value(val, open);
		double pdiff = fabs(open - price.GetBuy()) * currency.GetRate2Pip();
		if(pdiff > 100)
		{
			misc::cout << "\nPrice rejected as too far from current level.";
			GetOption(val); // stop after message
			return;
		}
		price = fx::Price(open, open);
		currency = fx::Currency("EUR/USD", price, 5, 0.08, 10000);
	}

	double commission = 0;
	double interest = 0;

	ep = fx::Position("", "", currency, isBuy, amount, commission, interest);

	misc::cout << "\ndist of grid (dg)= "; GetOption(val); misc::to_value(val, dg);
	misc::cout << "\nposition amount (ha)= "; GetOption(val); misc::to_value(val, pa);
	misc::cout << "\ndist to exit (de)= "; GetOption(val); misc::to_value(val, de);
	misc::cout << "\nmax negative (mn)= "; GetOption(val); misc::to_value(val, maxn);
	misc::cout << "\nmax positive (mp)= "; GetOption(val); misc::to_value(val, maxp);


	fx::StrategyFixGrid::Ptr fg = 
		new fx::StrategyFixGrid(ep, wait, dg, pa, de, maxn, maxp, plugin);

	m_new_strategies.push_back(fg);
}

void MonitorApp::CreateNew2FGStrategy()
{
	std::map<misc::string, fx::Price> quotes;
	if(!m_session->GetOffer(quotes))
	{
		misc::cout << "\nCannot retrieve market offer.";
		ConfirmOption('y', 'y'); // stop after message
	}

	if(quotes.find("EUR/USD") == quotes.end())
	{
		misc::cout << "\nInstrument 'EUR/USD' invalid.";
		ConfirmOption('y', 'y'); // stop after message
		return;
	}


	// market entry level
	fx::Price price = quotes["EUR/USD"];	
	fx::Currency currency("EUR/USD", price, 5, 0.08, 10000);
	fx::Position ep;
	bool isBuy = false;
	double amount = 0;
	// strategy
	bool wait = false;
	double dbg = 0;
	double dg = 0;
	double pa = 0;
	double de = 0;
	double maxn = 0;
	double maxp = 0;
	fx::MarketPlugin::Ptr plugin = m_session->GetMarketPlugin();

	misc::string val;

	misc::cout << "\nCreate a new 2(Double) Fix Grid strategy";
	misc::cout << "\nInstrument       = " << currency.GetSymbol().c_str();
	misc::cout << "\nBuy/Sell ? I choose !"; isBuy = true;
	misc::cout << "\nAmount (k)       = "; GetOption(val); misc::to_value(val, amount);
	misc::cout << "\nPrice            = " << 
		" B: " << misc::from_value(price.GetBuy(), 5) <<
		" S: " << misc::from_value(price.GetSell(), 5);

	misc::cout << "\nWant to enter at different price y/N = ";
	if(ConfirmOption('y', 'Y'))
	{
		wait = true;
		misc::cout << "\nOpen price = "; GetOption(val);
		double open = 0;
		misc::to_value(val, open);
		double pdiff = fabs(open - price.GetBuy()) * currency.GetRate2Pip();
		if(pdiff > 100)
		{
			misc::cout << "\nPrice rejected as too far from current level.";
			GetOption(val); // stop after message
			return;
		}
		price = fx::Price(open, open);
		currency = fx::Currency("EUR/USD", price, 5, 0.08, 10000);
	}

	double commission = 0;
	double interest = 0;

	ep = fx::Position("", "", currency, isBuy, amount, commission, interest);

	misc::cout << "\ndist between grids(dbg)= "; GetOption(val); misc::to_value(val, dbg);
	misc::cout << "\ndist of one grid   (dg)= "; GetOption(val); misc::to_value(val, dg);
	misc::cout << "\nposition amount    (pa)= "; GetOption(val); misc::to_value(val, pa);
	misc::cout << "\ndist to exit       (de)= "; GetOption(val); misc::to_value(val, de);
	misc::cout << "\nmax negative       (mn)= "; GetOption(val); misc::to_value(val, maxn);
	misc::cout << "\nmax positive       (mp)= "; GetOption(val); misc::to_value(val, maxp);


	fx::Strategy2FixGrid::Ptr hfg = 
		new fx::Strategy2FixGrid(ep, wait, dbg, dg, pa, de, maxn, maxp, plugin);

	m_new_strategies.push_back(hfg);
}

void MonitorApp::ShowNewStrategies()
{
	StrategyOutputVisitor visitor(misc::cout);
	for(size_t i = 0; i < m_new_strategies.size(); ++i)
	{
		misc::cout << "\n[" << i << "] ";
		fx::StrategyBase::Ptr s = m_new_strategies[i];
		s->AcceptVisitor(visitor);
	}

	if(m_new_strategies.empty())
		misc::cout << "\n0 new strategies.";
	ConfirmOption('y', 'Y'); // stop after listing
}

void MonitorApp::EraseNewStrategy()
{
	if(m_new_strategies.empty())
	{
		misc::cout << "\nNothing to erase.";
		ConfirmOption('y', 'Y');
		return;
	}

	misc::string val;
	misc::cout << "\nIndex of strategy to erase= ";
	GetOption(val);
	int ival=0;
	misc::to_value(val, ival);
	if(ival + 1 > (int)m_new_strategies.size())
	{
		misc::cout << "\nIndex should be inside [0,";
		misc::cout << m_new_strategies.size()-1;
		misc::cout << "]";
		return;
	}
	
	Strategies::iterator it = (m_new_strategies.begin() + ival);
	
	misc::cout << "\nConfirm [y/Y]= ";
	if(!ConfirmOption('y', 'Y'))
		return;
		
	m_new_strategies.erase(it);
	misc::cout << "\nErased";
	ConfirmOption('y', 'Y'); // stop after listing
}


//##############################################################################
StrategyOutputVisitor::StrategyOutputVisitor(std::ostream& stream)
	: m_out(stream)
{
}

void StrategyOutputVisitor::Visit(fx::StrategyBase&)
{
	throw misc::exception("Cannot visit abstract class.");
}

void StrategyOutputVisitor::Visit(fx::StrategyHedgeFixGrid& tv)
{
	m_out << tv.ToString().c_str();
}

void StrategyOutputVisitor::Visit(fx::Strategy2HedgeFixGrid& tv)
{
	m_out << tv.ToString().c_str();
}

void StrategyOutputVisitor::Visit(fx::StrategyFixGrid& tv)
{
	m_out << tv.ToString().c_str();
}

void StrategyOutputVisitor::Visit(fx::Strategy2FixGrid& tv)
{
	m_out << tv.ToString().c_str();
}