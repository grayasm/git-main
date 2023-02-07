/*
Copyright (C) 2018 Mihai Vasilian
*/


#include "RealEngine.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "ErrorCodes.hpp"
#include "StrategyRenkoAtr.hpp"
#include "MarketPlugin4fxcm.hpp"


void RealEngine()
{
    fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
    fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");


    // checkObligatoryParams
    if (loginParams->GetLogin().empty() ||
        loginParams->GetPassword().empty() ||
        loginParams->GetUrl().empty() ||
        loginParams->GetConnection().empty())
        return;


    bool isConnected = false;
    int hOpen = 7;
    int hClose = 16;
    double renkoMin = 15;
    fx::Offer offer;
    stl::string instrument("EUR/USD");
    fxcm::Session session(*loginParams, *iniParams);
    MarketPlugin4fxcm plugin(&session, *iniParams);
    fx::StrategyRenkoAtr strategy(&plugin, instrument, renkoMin, hOpen, hClose);
    

    while (true)
    {
        // outside trading hours?
        sys::time tnow(::time(NULL));
        if ((tnow.wday() == sys::time::SAT) ||
            (tnow.wday() == sys::time::FRI && tnow.hour_() >= 21) ||
            (tnow.wday() == sys::time::SUN && tnow.hour_() < 21))
        {
            if (isConnected)
            {
                if (session.Logout())
                    isConnected = false;
            }

            // idle 1m
            msleep(1000ul * sys::time::minSEC);
            continue;
        }

        // trading is active
        if (!isConnected)
        {
            isConnected = session.Login();
            if (isConnected)
            {
                session.GetOffers();
                msleep(3000); // wait 3 sec to fill the price feed
            }
        }

        if (!isConnected)
        {
            // idle 1min
            msleep(1000ul * sys::time::minSEC);
            continue;
        }

        // connected and getting quotes
        msleep(1000);
        
        int ret = session.GetLastOffer(offer, instrument.c_str());
        if (ret != fxcm::ErrorCodes::ERR_SUCCESS)
            break; // error with the price feed

        strategy.Update(offer);

        if (strategy.IsCancelled())
            break; // error with the strategy

    } // while

    session.Logout();
}
