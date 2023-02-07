/*
Copyright (C) 2014 Mihai Vasilian
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
        typedef std::map<stl::string, double>      PipCostMap;
        typedef std::map<stl::string, fx::Offer>   OffersMap;

		PipCost();
		
		PipCost(const PipCost&) = delete;
		PipCost& operator=(const PipCost&) = delete;

		double CalcPipCost(
            const stl::string& instrument,
			const stl::string& acc_symbol,
			int iBaseUnitSize,
            const OffersMap& offers) const;

	private:
        PipCostMap      m_nonCalculable;
	};
} // namespace

#endif // __PipCost_hpp__