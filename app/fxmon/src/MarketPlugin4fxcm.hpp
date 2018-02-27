/*
	Copyright (C) 2018 Mihai Vasilian

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


#ifndef __MarketPlugin4fxcm_hpp__
#define __MarketPlugin4fxcm_hpp__

#include "MarketPlugin.hpp"
#include "Session.hpp"


class MarketPlugin4fxcm : public fx::MarketPlugin
{
public:
	MarketPlugin4fxcm(	fxcm::Session* session,
						const fxcm::IniParams& iniParams);

	~MarketPlugin4fxcm();

	// --- virtual table ---
	void OpenPosition(	const fx::Offer& offer,
						int lots,
						bool buy,
						misc::vector<fx::Position>& result);

	void ClosePosition(	const fx::Offer& offer,
						const fx::Position& pos,
						misc::vector<fx::Position>& result);
	// --- end of virtual table ---

private:
	void Log(const misc::string& msg);

private:
	fxcm::Session*		m_session;
	fxcm::IniParams		m_iniParams;
};

#endif // __MarketPlugin4fxcm_hpp__
