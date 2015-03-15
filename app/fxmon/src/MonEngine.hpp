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


#ifndef __MonEngine_hpp__
#define __MonEngine_hpp__


#include "autoptr.hpp"
#include "vector.hpp"
#include "MonSession.hpp"
#include "StrategyBase.hpp"
#include "MonNotificationPlugin.hpp"



class MonEngine
{
public:
	typedef misc::autoptr<MonEngine> Ptr;
	MonEngine();
	~MonEngine();

	//! Set parameters
	void SetIniParams(const MonitorIni& params);
	//! Add a strategy to the engine.
	bool Add(const fx::StrategyBase::Ptr& s);
	//! Register a callback plugin.
	bool Register(const MonNotificationPlugin::Ptr& plugin);
	//! Set current session.
	bool SetSession(const MonSession::Ptr& session);

	//! Start execution.
	bool Start();
	//! Stop execution.
	bool Stop();


private:
	// non copyable
	MonEngine(const MonEngine&);
	MonEngine& operator=(const MonEngine&);
	
	
	void UpdateStrategies();
	void UpdatePlugins();	
	typedef misc::vector<fx::StrategyBase::Ptr> Strategies;
	void OnUpdateFailed(Strategies& strategies, Strategies::iterator& it) const;
	void OnExit();
	
	MonitorIni									m_params;		// initialization params
	MonSession::Ptr								m_session;		// current active session
	Strategies									m_strategies;	// strategies
	misc::vector<MonNotificationPlugin::Ptr>	m_plugins;	// callbacks
	bool										m_running;	// true while engine is on
	
	std::map<misc::string, fx::Price>			m_quotes;	// from session
};



#endif // __MonEngine_hpp__


