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



// C
// C++
// local
#include "fxcmSessionHelper.hpp"



namespace fxcm
{
	SessionHelper::SessionHelper()
	{
	}

	SessionHelper::~SessionHelper()
	{
	}

	//int SessionHelper::GerOriginAmount(const fx::Position& pos)
	//{
	//	const misc::string& symbol = pos.GetCurrency().GetSymbol();
	//	bool buy = pos.IsBuy();
	//	int amount = (int)pos.GetAmount();		
	//	const SymbolSettings& instrumentSettings = 
	//		m_session->m_tradingSettings->GetTradingSettings(symbol);
	//	int iBaseUnitSize = instrumentSettings.m_baseUnitSize;
	//	int iAmount = iBaseUnitSize * amount;
	//	return iAmount;
	//}
}