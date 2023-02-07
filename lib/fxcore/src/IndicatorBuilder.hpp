/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __IndicatorBuilder_hpp__
#define __IndicatorBuilder_hpp__

#include "MarketPlugin.hpp"
#include "vector.hpp"
#include "time.hpp"
#include "IND.hpp"
#include "Offer.hpp"



namespace fx
{
    class IndicatorBuilder
    {
    public:
        IndicatorBuilder() = delete;
        ~IndicatorBuilder() = delete;

        static void Build(
            fx::MarketPlugin* plugin,
            const fx::Offer& offer,
            stl::vector<fx::IND*>& indicators);

    private:
        static void Update(
            const fx::Offer& offer,
            const fx::OHLCPrice& ohlc,
            stl::vector<fx::IND*>& indicators);

        static void Check(stl::vector<fx::IND*>& indicators);
    };
} // namespace

#endif // __IndicatorBuilder_hpp__
