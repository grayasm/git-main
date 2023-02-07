/*
Copyright (C) 2018 Mihai Vasilian
*/


#ifndef __MarketPlugin4fxcm_hpp__
#define __MarketPlugin4fxcm_hpp__

#include "MarketPlugin.hpp"
#include "Session.hpp"


class MarketPlugin4fxcm : public fx::MarketPlugin
{
public:
    MarketPlugin4fxcm(  fxcm::Session* session,
                        const fxcm::IniParams& iniParams);
    ~MarketPlugin4fxcm();

    MarketPlugin4fxcm(const MarketPlugin4fxcm&) = delete;
    MarketPlugin4fxcm& operator=(const MarketPlugin4fxcm&) = delete;

    // --- virtual table ---
    int OpenPosition(   const fx::Offer& offer,
                        int lots,
                        bool buy,
                        stl::vector<fx::Position>& result);

    int ClosePosition(  const fx::Offer& offer,
                        const fx::Position& pos,
                        stl::vector<fx::Position>& result);

    int GetOHLCPrices(  const stl::string& instrument,
                        const stl::string& timeframe,
                        const sys::time& from,
                        const sys::time& to,
                        stl::vector<fx::OHLCPrice>& result);
    // --- end of virtual table ---

private:
    void Log(const stl::string& msg);

private:
    fxcm::Session*        m_session;
    fxcm::IniParams        m_iniParams;
};

#endif // __MarketPlugin4fxcm_hpp__
