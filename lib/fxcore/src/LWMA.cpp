/*
Copyright (C) 2018 Mihai Vasilian
*/

/*
    http://www.20minutetraders.com/learning/moving_averages/linear-weighted-moving-average.php
    A linear weighted moving average assigns more weight to the more
    recent prices. While weighting is not as significant for a 5 day moving
    average, there is a substantial difference in a longer period, such as a
    50 day moving average.
    In a Simple Moving Average the price data have an equal weight in the
    computation of the average, while for LWMA the value is incremented.

    LWMA(i) = SUM( Close(i) * i, N ) / SUM(i, N);    where:
    
    SUM = sum
    Close(i) = closing price of the candle
    SUM(i, N) =  total sum of weight coefficients
    N = smoothing period
*/

#include "LWMA.hpp"


namespace fx
{
    LWMA::LWMA()
    {
        Init();
    }

    LWMA::LWMA(
        const stl::string& instrument,
        int period,
        Timeframe sec,
        BarType barType,
        PriceOrigin po)
    {
        if (period < 2)
            throw stl::exception("LWMA period must be greater than 1");

        Init();

        m_instrument = instrument;
        m_period = period;
        m_timeframe = sec;
        m_barType = barType;
        m_priceOrigin = po;
        switch (barType)
        {
            case fx::SMA::BT_BAR:
            {
                m_bar = new fx::BAR(instrument, period, sec);
                break;
            }
            case fx::SMA::BT_HABAR:
            {
                m_bar = new fx::HABAR(instrument, period, sec);
                break;
            }
            default:
                throw stl::exception("SMA unknown BAR type");
        }
    }

    LWMA::~LWMA()
    {
        if (m_bar)
            delete m_bar;
    }

    LWMA::LWMA(const LWMA& tc)
    {
        Init();

        *this = tc;
    }

    LWMA& LWMA::operator = (const LWMA& tc)
    {
        if (this != &tc)
        {
            m_instrument = tc.m_instrument;
            m_period = tc.m_period;
            m_timeframe = tc.m_timeframe;
            m_barType = tc.m_barType;
            m_priceOrigin = tc.m_priceOrigin;
            if (tc.m_bar)
            {
                switch (tc.m_barType)
                {
                    case fx::SMA::BT_BAR:
                    {
                        fx::BAR* ptr = static_cast<fx::BAR*>(tc.m_bar);
                        if (m_bar)
                            delete m_bar;
                        m_bar = new fx::BAR(*ptr);
                        break;
                    }
                    case fx::SMA::BT_HABAR:
                    {
                        fx::HABAR* ptr = static_cast<fx::HABAR*>(tc.m_bar);
                        if (m_bar)
                            delete m_bar;
                        m_bar = new fx::HABAR(*ptr);
                        break;                                          
                    }
                    default:
                        throw stl::exception("LWMA unknown BAR type");
                } // switch
            }
            else
            {
                if (m_bar)
                    delete m_bar;
                m_bar = NULL;
            }
            m_sumMinus1P = tc.m_sumMinus1P;
        }
        return *this;
    }

    const stl::string& LWMA::GetInstrument() const
    {
        return m_instrument;
    }

    int LWMA::GetPeriod() const
    {
        return m_period;
    }

    LWMA::Timeframe LWMA::GetTimeframe() const
    {
        return m_timeframe;
    }

    bool LWMA::IsValid() const
    {
        return (m_period > 1 &&
                m_period == m_bar->GetOHLCList().size() &&
                m_sumMinus1P.GetBuy() != 0 &&
                m_sumMinus1P.GetSell() != 0);
    }

    void LWMA::Update(const fx::Offer& offer)
    {
        if (m_instrument != offer.GetInstrument())
            throw stl::exception("LWMA offer is invalid");

        // offer will paint a new bar?
        bool isNew = m_bar->IsNew(offer);

        m_bar->Update(offer);
            
        const fx::BARB::OHLCPriceList& ohlcList = m_bar->GetOHLCList();
        if (isNew && ohlcList.size() == m_period)
        {
            //  LWMA(i) will use (m_period - 1) prices + the current candle(i)
            double buy = 0, sell = 0;
            fx::BARB::OHLCPriceList::const_iterator it = ohlcList.begin();
            it++;
            size_t i = 1;
            for (; it != ohlcList.end(); ++it, ++i)
            {
                if (m_priceOrigin == fx::SMA::PRICE_OPEN)
                {
                    buy += (it->GetAskOpen() * i);
                    sell += (it->GetBidOpen() * i);
                }
                else if (m_priceOrigin == fx::SMA::PRICE_CLOSE)
                {
                    buy += (it->GetAskClose() * i);
                    sell += (it->GetBidClose() * i);
                }
                else
                    throw stl::exception("LWMA unknown price origin");                
            }
            m_sumMinus1P = fx::Price(buy, sell);
        }
    }

    const sys::time&  LWMA::GetRefTime() const
    {
        return m_bar->GetRefTime();
    }

    void  LWMA::GetValue(fx::Price& average) const
    {
        if (m_period < 2 ||
            m_bar->GetOHLCList().size() != m_period ||
            m_sumMinus1P.GetBuy() == 0 ||
            m_sumMinus1P.GetSell() == 0)
        {
            throw stl::exception("LWMA is invalid");
        }

        const fx::OHLCPrice& ohlc = m_bar->GetOHLC();
        double buy = 0, sell = 0;

        if (m_priceOrigin == fx::SMA::PRICE_OPEN)
        {
            buy = m_sumMinus1P.GetBuy() + ohlc.GetAskOpen() * m_period;
            sell = m_sumMinus1P.GetSell() + ohlc.GetBidOpen() * m_period;
        }
        else if (m_priceOrigin == fx::SMA::PRICE_CLOSE)
        {
            buy = m_sumMinus1P.GetBuy() + ohlc.GetAskClose() * m_period;
            sell = m_sumMinus1P.GetSell() + ohlc.GetBidClose() * m_period;
        }
        else
            throw stl::exception("LWMA unknown price origin");

        double sumiN = m_period * (m_period + 1) / 2;
        buy /= sumiN;
        sell /= sumiN;
        average = fx::Price(buy, sell);
    }

    void  LWMA::Init()
    {
        m_instrument = "";
        m_period = -1;
        m_timeframe = 0;
        m_barType = fx::SMA::BT_BAR;
        m_priceOrigin = fx::SMA::PRICE_CLOSE;
        m_bar = NULL;
        m_sumMinus1P = fx::Price(0, 0);
    }
} // namespace
