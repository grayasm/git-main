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



#ifndef __Serializer_hpp__
#define __Serializer_hpp__



#include "stream.hpp"
#include "Transaction.hpp"
#include "Position.hpp"
#include "StrategyHedgeFixGrid.hpp"
#include "Strategy2HedgeFixGrid.hpp"
#include "StrategyFixGrid.hpp"
#include "Strategy2FixGrid.hpp"

namespace fx
{
	class Serializer
	{
	public:		
		Serializer(const misc::string& file);
		~Serializer();		
		Serializer& operator<<(const StrategyHedgeFixGrid& s);
		Serializer& operator<<(const Strategy2HedgeFixGrid& s);
		Serializer& operator<<(const StrategyFixGrid& s);
		Serializer& operator<<(const Strategy2FixGrid& s);

	private:
		Serializer(const Serializer&);
		Serializer& operator=(const Serializer&);

		Serializer& operator<<(const Price& price);	
		Serializer& operator<<(const Currency& currency);
		Serializer& operator<<(const Position& p);
		Serializer& operator<<(const Transaction& t);		
		Serializer& operator<<(const FixGridPositionStub& ps);
		
		misc::ofstream*	m_out;		
	};
} // namespace


#endif // __Serializer_hpp__

