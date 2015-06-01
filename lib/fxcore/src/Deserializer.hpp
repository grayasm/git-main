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




#ifndef __Deserializer_hpp__
#define __Deserializer_hpp__


#include <fstream>
#include "stream.hpp"
#include "Transaction.hpp"
#include "Position.hpp"
#include "StrategyHedgeFixGrid.hpp"
#include "Strategy2HedgeFixGrid.hpp"
#include "StrategyFixGrid.hpp"
#include "Strategy2FixGrid.hpp"


namespace fx
{
	class Deserializer
	{
	public:
		Deserializer(const misc::string& file);
		~Deserializer();

		//! Restore strategies from serialized file.
		void Deserialize();

		//! Market plugin to be used by strategies.
		void SetPlugin(fx::MarketPlugin::Ptr plugin);

		//! Returns the strategies array.
		const misc::vector<fx::StrategyBase::Ptr>& GetData() const;
		
	private:
		Deserializer(const Deserializer&);
		Deserializer& operator=(const Deserializer&);

		void Reset();
		void Deserialize(fx::Transaction& t, size_t size);
		void Deserialize(fx::Position& p);
		void Deserialize(fx::StrategyHedgeFixGrid& fgs);
		void Deserialize(fx::StrategyHedgeFixGrid::Grid& grid, size_t size);
		void Deserialize(fx::FixGridPositionStub& ps);
		void Deserialize(fx::Strategy2HedgeFixGrid& h2fgs);
		void Deserialize(fx::StrategyFixGrid& fgs);
		void Deserialize(fx::Strategy2FixGrid& _2fgs);
				
		misc::string				m_file;
		misc::ifstream*				m_out;
		fx::MarketPlugin::Ptr		m_plugin;

		// deserialized data
		misc::vector<fx::StrategyBase::Ptr> m_data;
	};
} // namespace


#endif // __Deserializer_hpp__