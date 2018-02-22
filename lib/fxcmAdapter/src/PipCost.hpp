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


#ifndef __PipCost_hpp__
#define __PipCost_hpp__


#include <map>
#include "string.hpp"
#include "Offer.hpp"


namespace fxcm
{
	class PipCost
	{
	public:
		PipCost();
		
		PipCost(const PipCost&) = delete;
		PipCost& operator=(const PipCost&) = delete;

		double CalcPipCost(
			const fx::Offer& offer,
			const misc::string& acc_symbol,
			int iBaseUnitSize) const;

	private:
		std::map<misc::string, double>	m_nonCalculable;
	};
} // namespace

#endif // __PipCost_hpp__