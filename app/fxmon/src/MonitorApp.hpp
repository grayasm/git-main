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


#ifndef __MonitorApp_hpp__
#define __MonitorApp_hpp__


// c
// c++
// local
#include "MonitorIni.hpp"
#include "fxcmIniParams.hpp"
#include "MonSession.hpp"
#include "MonEngine.hpp"
#include "audit.hpp"




class MonitorApp
{
public:
	MonitorApp();
	~MonitorApp();

	bool Menu();

private:
	//! methods
	bool Create();	
	bool Run();
	void ShowMenu();
	bool ProcessOption();
	bool ConfirmOption(char key, char KEY);
	bool GetOption(misc::string& val);
	void Deserialize();
	void ListDeserialized();
	void CreateNewStrategy();
	void CreateNewHFGStrategy();
	void CreateNewHFGStrategies();
	void CreateNew2HFGStrategy();
	void CreateNewFGStrategy();
	void ShowNewStrategies();
	void EraseNewStrategy();
	


private:
	//! members
	MonitorIni			m_monitorIni;
	fxcm::IniParams		m_sessionIni;
	MonSession::Ptr		m_session;
	MonEngine::Ptr		m_engine;

	typedef misc::vector<fx::StrategyBase::Ptr> Strategies;
	Strategies m_deserialized_strategies;
	Strategies m_new_strategies;
};

//##############################################################################
class StrategyOutputVisitor : public fx::StrategyVisitor
{
public:
	StrategyOutputVisitor(std::ostream& stream);

	//! --- virtual table ---
	void Visit(fx::StrategyBase& tv);
	void Visit(fx::StrategyHedgeFixGrid& tv);
	void Visit(fx::Strategy2HedgeFixGrid& tv);
	void Visit(fx::StrategyFixGrid& tv);
	//! --- end of vtable ---

private:
	StrategyOutputVisitor(const StrategyOutputVisitor&);
	StrategyOutputVisitor& operator=(const StrategyOutputVisitor&);

private:
	std::ostream& m_out;
};
//##############################################################################

#endif // __MonitorApp_hpp__

