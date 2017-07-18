/*
Copyright (C) 2017 Mihai Vasilian

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

contact: grayasm@gmail.com
*/

#include "OfferCollection.hpp"
#include "autocritical_section.hpp"

namespace fxcm
{
	OfferCollection::OfferCollection()
	{
	}

	OfferCollection::~OfferCollection()
	{
	}

	void OfferCollection::AddOffer(const fx::Offer& offer)
	{
		misc::autocritical_section autoCS(m_criticalsection);
		m_offersVec.push_back(offer);
	}

	size_t OfferCollection::FindOffer(const char* id)
	{
		misc::autocritical_section autoCS(m_criticalsection);
		for (size_t i = 0; i < m_offersVec.size(); ++i)
		{
			if (m_offersVec[i].GetId() == id)
				return i;
		}
		return (size_t)-1;
	}

	size_t OfferCollection::Size()
	{
		misc::autocritical_section autoCS(m_criticalsection);
		return m_offersVec.size();
	}

	fx::Offer* OfferCollection::Get(size_t index)
	{
		misc::autocritical_section autoCS(m_criticalsection);
		return &(m_offersVec[index]);
	}

	void OfferCollection::Clear()
	{
		misc::autocritical_section autoCS(m_criticalsection);
		m_offersVec.clear();
	}
} // namespace