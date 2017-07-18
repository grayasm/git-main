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

#ifndef __OfferCollection_hpp__
#define __OfferCollection_hpp__

#include "Offer.hpp"
#include "critical_section.hpp"


namespace fxcm
{
	class OfferCollection
	{
	public:
		OfferCollection();
		~OfferCollection();

		void AddOffer(const fx::Offer& offer);
		size_t FindOffer(const char* id);
		size_t Size();
		fx::Offer* Get(size_t index);
		void Clear();

	private:
		OfferCollection(const OfferCollection&);
		OfferCollection& operator=(const OfferCollection&);

	private:
		std::vector<fx::Offer>		m_offersVec;
		misc::critical_section		m_criticalsection;
	};
} // namespace


#endif // __OfferCollection_hpp__
