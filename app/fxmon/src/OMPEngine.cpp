/*
Copyright (C) 2018 Mihai Vasilian
*/

#include "OMPEngine.hpp"
#include <omp.h>
#include <map>
#include <functional>
#include "unistd.hpp"
#include "stream.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "ErrorCodes.hpp"
#include "IndicatorBuilder.hpp"
#include "StrategySMACross.hpp"
#include "MarketPlugin4backtest.hpp"
#include "HistdatacomReader.hpp"


void OMPEngine()
{
    fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
    fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");


    // checkObligatoryParams
    if (loginParams->GetLogin().empty() ||
        loginParams->GetPassword().empty() ||
        loginParams->GetUrl().empty() ||
        loginParams->GetConnection().empty())
        return;

    if (iniParams->GetEnableLogging())
        return; // cannot let > 500 strategies write in one file; turn it off;


    // MarketPlugin4backtest needs a valid session to calculate things
    // like the pip cost, MMR, iBaseUnitSize, etc.
    // Depending on the traded instrument, the pipCost calculator may need
    // access to other offers to convert the quote into account currency.
    stl::string instrument("EUR/USD");
    int ret = 0;
    fx::Offer offer;

    fxcm::Session session(*loginParams, *iniParams);
    session.Login();
    session.GetOffers();
    msleep(3000); // wait to get the offers
    
    ret = session.GetLastOffer(offer, instrument.c_str());
    if (ret != fxcm::ErrorCodes::ERR_SUCCESS ||
        offer.GetInstrument().empty() ||
        offer.GetPointSize() == 0 ||
        offer.GetPrecision() == 0)
        return;


    MarketPlugin4backtest plugin(&session, *iniParams);
    HistdatacomReader oreader(offer, 2017);
    sys::time reftime;
    stl::vector<fx::IND*> smaVec;
    stl::vector<fx::StrategySMACross*> strategyVec;
    typedef stl::pair<stl::string, fx::StrategySMACross*> CrossPair;
    stl::vector<CrossPair> crossVec;
    
    
    // SMA(2, 1H) -> SMA(48, 1H)
    // SMA(2, 1D) -> SMA(60, 1D)
    for (int i = 2; i <= 48; ++i)    // 48hours
    {
        fx::SMA* sma = new fx::SMA(instrument, i, sys::time::hourSEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);
        smaVec.push_back(sma);
    }

    for (int i = 2; i <= 20; ++i)    // 60days
    {
        fx::SMA* sma = new fx::SMA(instrument, i, sys::time::daySEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);
        smaVec.push_back(sma);
    }
    
    if (!oreader.GetOffer(offer))
        return; // cannot get the offer?

    reftime = offer.GetTime();
    stl::cout << reftime.tostring().c_str() << std::endl;

    
    fx::IndicatorBuilder::Build(&plugin, offer, smaVec);
    
    
    for (int i = 0; i < smaVec.size()-1; ++i)
    {
        for (int j = i + 1; j < smaVec.size(); ++j)
        {
            fx::SMA* sma1 = static_cast<fx::SMA*>(smaVec[i]);
            fx::SMA* sma2 = static_cast<fx::SMA*>(smaVec[j]);

            fx::StrategySMACross* strategy =
                new fx::StrategySMACross(
                &plugin,
                instrument,
                *sma1,
                *sma2);
            strategyVec.push_back(strategy);

            std::stringstream ss;
            ss << "SMA1(" << sma1->GetPeriod() << ",";
            ss << (sma1->GetTimeframe() == sys::time::hourSEC ? "H) " : "D) ");
            ss << "SMA2(" << sma2->GetPeriod() << ",";
            ss << (sma2->GetTimeframe() == sys::time::hourSEC ? "H) " : "D) ");
            stl::string str(ss.str().c_str());
            CrossPair cpair(str, strategy);
            crossVec.push_back(cpair);
        }
    }
    

    while (true)
    {
        if (!oreader.GetOffer(offer))
            break;

        if (reftime.mon_() != offer.GetTime().mon_())
        {
            reftime = offer.GetTime();
            // show some progress, otherwise confusing and very slow
            stl::cout << reftime.tostring().c_str() << std::endl;
        }

        // check for outside trading hours
        sys::time tnow = offer.GetTime();
        if ((tnow.wday() == sys::time::SAT) ||
            (tnow.wday() == sys::time::FRI && tnow.hour_() >= 22) ||
            (tnow.wday() == sys::time::SUN && tnow.hour_() < 22))
        {
            continue;
        }


        int i = 0;
#pragma omp parallel shared(strategyVec, offer) private(i)
        {
#pragma omp for
            for (i = 0; i < strategyVec.size(); ++i)
            {
                strategyVec[i]->Update(offer);

                // printf("thread %d strategyVec[%d]\n", omp_get_thread_num(), i);
            }
        } // omp parallel
        
    } // while

    session.Logout();

    std::function<bool(const CrossPair&, const CrossPair&)> lmdbpred
        = [](const CrossPair& cp1, const CrossPair& cp2) -> bool
    {
        return (cp1.second->GetClosedGPL() > cp2.second->GetClosedGPL());
    };

    stl::sort(crossVec.begin(), crossVec.end(), lmdbpred);

    // use logging only summary data
    FILE* fp = fopen(iniParams->GetLoggingFile().c_str(), "w+");

    
    for (stl::vector<CrossPair>::iterator it = crossVec.begin();
         it != crossVec.end() && fp != NULL; ++it)
    {
        std::stringstream ss;
        ss << it->first.c_str();
        ss << " PL=" << it->second->GetClosedPL();
        ss << " GPL=" << it->second->GetClosedGPL() << std::endl;
        std::string str(ss.str());
        fwrite(str.c_str(), sizeof(char), str.size(), fp);
    }

    if (fp) fclose(fp);

    stl::cout << "Log file update.\nDestroying...\n";

    for (int i = 0; i < strategyVec.size(); ++i)
        delete strategyVec[i];

    for (int i = 0; i < smaVec.size(); ++i)
        delete smaVec[i];
}
