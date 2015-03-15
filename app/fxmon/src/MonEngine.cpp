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


#include <time.h>
#include <math.h>
#include "MonEngine.hpp"
#include "stream.hpp"
#include "strconv.hpp"
#include "Serializer.hpp"
#include "StrategyBase.hpp"
#include "StrategyHedgeFixGrid.hpp"


MonEngine::MonEngine()
{
	// m_params;
	m_session = 0;
	m_strategies.clear();
	m_plugins.clear();
	m_running = false;
}

MonEngine::~MonEngine()
{
}

void MonEngine::SetIniParams(const MonitorIni& params)
{
	m_params = params;
}

bool MonEngine::Add(const fx::StrategyBase::Ptr& s)
{
	m_strategies.push_back(s);
	
	return true;
}

bool MonEngine::Register(const MonNotificationPlugin::Ptr& plugin)
{
	m_plugins.push_back(plugin);

	return true;
}

bool MonEngine::SetSession(const MonSession::Ptr& session)
{
	m_session = session;

	return true;
}


bool MonEngine::Start()
{
	if(m_session.IsNull() ||
		m_strategies.empty() ||
		m_plugins.empty() ||
		m_running)
	{
		misc::cout << "\nMonitor engine is not initialized correctly.";
		return false;
	}

	m_running = true;
	while(m_running)
	{
		UpdateStrategies();
		UpdatePlugins();
	}

	OnExit();

	// engine off
	return false;
}

bool MonEngine::Stop()
{
	m_running = false;

	return true;
}

void MonEngine::UpdateStrategies()
{
	if(m_strategies.empty())
	{
		m_running = false;
		return;
	}

	fx::Price price;
	if(!m_session->GetOffer(m_quotes))
		return;

	//TODO: need to take this from each strategy as they may work in different pairs.
	price = m_quotes["EUR/USD"];
	
	for(Strategies::iterator it = m_strategies.begin(); it != m_strategies.end(); /*..*/)
	{
		fx::StrategyBase::Ptr& sptr = *it;
		bool bInUse = sptr->Update(price);

		if(!bInUse)
		{
			// must increment iterator to avoid dead lock
			OnUpdateFailed(m_strategies, it);
		}
		else
		{
			++it;
		}		
	}
}

void MonEngine::UpdatePlugins()
{
	for(size_t i = 0; i < m_plugins.size(); ++i)
		m_plugins[i]->OnUpdate();
}

class StrategyWriterVisitor : public fx::StrategyVisitor
{
public:
	StrategyWriterVisitor(fx::Serializer& sz)
		: m_serializer(sz)
	{
	}

	void Visit(fx::StrategyBase&)
	{
		throw misc::exception("Not implemented.");
	}

	void Visit(fx::StrategyHedgeFixGrid& tv)
	{
		m_serializer << tv;
	}

	void Visit(fx::Strategy2HedgeFixGrid& tv)
	{
		m_serializer << tv;
	}

	void Visit(fx::StrategyFixGrid& tv)
	{
		m_serializer << tv;
	}

private:
	//! non copyable
	StrategyWriterVisitor(const StrategyWriterVisitor&);
	StrategyWriterVisitor& operator=(const StrategyWriterVisitor&);

	fx::Serializer& m_serializer;
};

void MonEngine::OnUpdateFailed(Strategies& strategies, Strategies::iterator& it) const
{
	bool dumpStrategyOutcome = m_params.GetDumpStrategyOutcome();
	bool keepStrategyInProfit = m_params.GetKeepStrategyInProfit();
	bool keepStrategyInLoss = m_params.GetKeepStrategyInLoss();

	fx::StrategyBase::Ptr strategy = *it;
	double gpl = strategy->GetGPL();
	misc::string sgpl = misc::from_value(fabs(gpl), 2);
	bool bInProfit = (gpl > 0);
	if(dumpStrategyOutcome)
	{
		time_t rawtime;
		//struct tm* timeinfo;
		struct tm timeinfo;
		char buffer[80];
		time(&rawtime);
		//timeinfo = localtime(&rawtime);
		localtime_s(&timeinfo, &rawtime);
		strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", &timeinfo);
		
		misc::string fout(buffer);
		if(bInProfit)
		{
			fout += "_profit_";
			fout += sgpl;
			fout += ".txt";
		}
		else
		{
			fout += "_lost_";
			fout += sgpl;
			fout += ".txt";
		}

		fx::StrategyBase::Ptr strategy = *it;		
		fx::Serializer sz(fout);
		StrategyWriterVisitor visitor(sz);
		strategy->AcceptVisitor(visitor);
	}
	
	
	// Must increment the iterator to avoid the dead lock.
	if(bInProfit && keepStrategyInProfit)
	{
		strategy->ReInit();
		++it;
	}
	else if(!bInProfit && keepStrategyInLoss)
	{
		strategy->ReInit();
		++it;
	}
	else
	{
		Strategies::iterator tmp = strategies.erase(it);
		it = tmp;
	}
}

void MonEngine::OnExit()
{
	// Save data of currently running strategies!
	fx::Serializer sz("trading.txt");
	for(Strategies::iterator it = m_strategies.begin(); it != m_strategies.end(); ++it)
	{
		fx::StrategyBase::Ptr strategy = *it;		
		StrategyWriterVisitor visitor(sz);
		strategy->AcceptVisitor(visitor);
	}	
}


