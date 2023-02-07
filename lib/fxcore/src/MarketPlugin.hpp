/*
Copyright (C) 2018 Mihai Vasilian
*/


#ifndef __MarketPlugin_hpp__
#define __MarketPlugin_hpp__


#include "vector.hpp"
#include "Offer.hpp"
#include "OHLCPrice.hpp"
#include "Position.hpp"



namespace fx
{
    /*  The core does not need to know login details, if or when to logout,
        or any other particular details about a broker. It is enough for now
        to provide few simple methods to open and close one or more positions.
        On SUCCESS return value is zero.
    */
    class MarketPlugin
    {
    public:
        virtual ~MarketPlugin();

        virtual int OpenPosition(   const fx::Offer& offer,
                                    int lots,
                                    bool buy,
                                    stl::vector<fx::Position>& result) = 0;

        virtual int ClosePosition(  const fx::Offer& offer,
                                    const fx::Position& pos,
                                    stl::vector<fx::Position>& result) = 0;

        virtual int GetOHLCPrices(  const stl::string& instrument,
                                    const stl::string& timeframe,
                                    const sys::time& from,
                                    const sys::time& to,
                                    stl::vector<fx::OHLCPrice>& result) = 0;
    };
} // namespace

#endif // __MarketPlugin_hpp__
