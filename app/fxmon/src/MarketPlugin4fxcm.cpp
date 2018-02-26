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

#include "MarketPlugin4fxcm.hpp"
#include "ErrorCodes.hpp"
#include "stream.hpp"



MarketPlugin4fxcm::MarketPlugin4fxcm(
	fxcm::Session* session,
	const fxcm::IniParams& iniParams)
{
	m_session = session;
	m_iniParams = iniParams;
}

MarketPlugin4fxcm::~MarketPlugin4fxcm()
{

}

void MarketPlugin4fxcm::OpenPosition(
	const fx::Offer& offer,
	int lots,
	bool buy,
	misc::vector<fx::Position>& result)
{
	int ret = m_session->OpenPosition(offer, lots, buy, result);

	if (ret != fxcm::ErrorCodes::ERR_SUCCESS)
	{
		 misc::cout << __FUNCTION__ <<
			 ": m_session->OpenPosition returned error=" <<
			 fxcm::ErrorCodes::GetText((fxcm::ErrorCodes::ErrorId)ret).c_str()
			 << std::endl;
	}

	misc::string message(offer.GetTime().tostring());
	message += " => Open Position: \n";
	result = fx::Transaction(); // clear the result

	for (size_t i = 0; i < openPositions.size(); ++i)
	{
		const fx::Position& pos = openPositions[i];
		result.Add(pos);
		message += pos.ToString();
		message += "\n";
	}

	Log(iniParams, message);
}

void MarketPlugin4fxcm::ClosePosition(
	const fx::Offer& offer,
	const fx::Position& pos,
	misc::vector<fx::Position>& result)
{

}