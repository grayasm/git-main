/*
Copyright (C) 2018 Mihai Vasilian
*/

#include "HistdatacomReader.hpp"
#include "unistd.hpp"
#include "filename.hpp"
#include "stream.hpp"


HistdatacomReader::HistdatacomReader(const fx::Offer& offer, int year)
{
    m_offer = offer;
    m_year = year;
    // ------------
    const stl::string& instrument = offer.GetInstrument();
    if (instrument == "EUR/USD" && m_year == 1900) LoadEURUSD1900();
    else if (instrument == "EUR/USD" && m_year == 2008) LoadEURUSD2008();
    else if (instrument == "EUR/USD" && m_year == 2014) LoadEURUSD2014();
    else if (instrument == "EUR/USD" && m_year == 2015) LoadEURUSD2015();
    else if (instrument == "EUR/USD" && m_year == 2016) LoadEURUSD2016();
    else if (instrument == "EUR/USD" && m_year == 2017) LoadEURUSD2017();
    else if (instrument == "EUR/USD" && m_year == 2018) LoadEURUSD2018();
    else if (instrument == "EUR/USD" && m_year == 2019) LoadEURUSD2019();
    else if (instrument == "EUR/JPY" && m_year == 2017) LoadEURJPY2017();
    else if (instrument == "USD/JPY" && m_year == 2017) LoadUSDJPY2017();
    else if (instrument == "GBP/JPY" && m_year == 2017) LoadGBPJPY2017();    
    else
        throw stl::exception("HistdatacomReader unknown instrument");

    m_ofvPos = 0;
    // m_offersVec; - empty
    m_ovPos = 0;
}

HistdatacomReader::~HistdatacomReader()
{
}

bool HistdatacomReader::GetOffer(fx::Offer& offer)
{
    if (m_ovPos < m_offersVec.size())
    {
        offer = m_offersVec[m_ovPos++];
        if (offer.GetPrecision() == 0 || offer.GetPointSize() == 0 ||
            offer.GetBid() == 0.0 || offer.GetAsk() == 0.0)
        {
            // invalid quote
            return GetOffer(offer);
        }

        return true;
    }

    if (m_ofvPos < m_offerFileVec.size())
    {
        m_offersVec.resize(0);
        m_ovPos = 0;
        ParseFile(m_offerFileVec[m_ofvPos++], m_offersVec);
        return GetOffer(offer);
    }

    return false;
}


void HistdatacomReader::ParseFile(
    const stl::string& filePath,
    stl::vector<fx::Offer>& result)
{
    sys::filename offerFile(filePath);
    if (!offerFile.access(F_OK))
        return; // error

    FILE* pf = fopen(offerFile.get_path().c_str(), "r");
    if (pf == NULL)
        return; // error

    const int bufsz = 1000000;
    char buf[bufsz];
    int bufmax = 0;
    int bufpos = 0;

    // assume EUR/USD for now
    fx::Offer offer(
        m_offer.GetOfferID(),
        m_offer.GetInstrument(),
        m_offer.GetPrecision(),    // precision
        m_offer.GetPointSize(),    // pointSize
        sys::time(),
        0,        // bid
        0,        // ask
        0,        // vol
        true);    // trading is open

    stl::string fline;
    char c;

    int year = 0;
    int month = 0;
    int day = 0;


    while (true) //(c = fgetc(pf)) != EOF)
    {
        if (bufpos < bufmax) {
            c = buf[bufpos++];
        }
        else if (!feof(pf)) {
            bufmax = fread(buf, sizeof(char), bufsz, pf);
            bufpos = 0;
            continue;
        }
        else {
            // end of stream
            break;
        }


        if (c == '\n')
        {
            char* pch;
            char str[1000];
            strcpy(str, fline.c_str());
            stl::string s1;
            int i = 0;

            pch = strtok(str, " ,");
            while (pch != NULL)
            {
                i++;
                // 20171201 000000043,1.191100,1.191140,0
                // 20171201 002359120,1.191100,1.191140,0
                if (i == 1)
                {
                    s1 = stl::string(pch);
                    int fulldate = 0;
                    stl::to_value(s1, fulldate);
                    year = fulldate / 10000;
                    month = (fulldate - year * 10000) / 100;
                    day = fulldate - year * 10000 - month * 100;
                }
                else if (i == 2)
                {
                    s1 = stl::string(pch);
                    int fulltime = 0;
                    stl::to_value(s1, fulltime);
                    int hour = fulltime / 10000000;
                    int min = fulltime / 100000;
                    if (min >= 100)
                        min -= hour * 100;
                    int milsec = fulltime - hour * 10000000 - min * 100000;
                    int sec = milsec / 1000;

                    sys::time::Month mon = (sys::time::Month)(sys::time::JAN + month - 1);

                    sys::time otime(year, mon, day, hour, min, sec);
                    // time is EST (Eastern Time without Daylight Saving)
                    // because I calculate with UTC makes sense to covert now
                    otime += 5 * sys::time::hourSEC;

                    offer.SetTime(otime);
                }
                else if (i == 3)
                {
                    s1 = stl::string(pch);
                    double bid = 0;
                    stl::to_value(s1, bid);
                    offer.SetBid(bid);                    
                }
                else if (i == 4)
                {
                    s1 = stl::string(pch);
                    double ask = 0;
                    stl::to_value(s1, ask);
                    offer.SetAsk(ask);
                }
                else if (i == 5)
                {
                    s1 = stl::string(pch);
                    double vol = 0;
                    stl::to_value(s1, vol);
                    offer.SetVolume(vol);
                }

                pch = strtok(NULL, ",=");
            } // while(pch)

            
            result.push_back(offer);
#ifdef DEBUG
            if (result.size() % 1000 == 0)
                stl::cout << "fetched " << result.size() << std::endl;
#endif

            fline.resize(0);
            continue;
        } // c == '\n'

        fline.append(1, c);
    }

    fclose(pf);
}

void HistdatacomReader::LoadEURUSD1900()
{
    LoadEURUSD2014();
    LoadEURUSD2015();
    LoadEURUSD2016();
    LoadEURUSD2017();
    LoadEURUSD2018();
    LoadEURUSD2019();
}

void HistdatacomReader::LoadEURUSD2008()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200801.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200801_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200802.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200802_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200803.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200803_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200803_3.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200804.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200804_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200804_3.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200805.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200805_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200806.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200806_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200807.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200807_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200808.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200808_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200808_3.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200809.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200809_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200809_3.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200809_4.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200810.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200810_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200810_3.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200810_4.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200810_5.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200811.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200811_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200811_3.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200811_4.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200812.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200812_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200812_3.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2008\\DAT_ASCII_EURUSD_T_200812_4.csv");
}

void HistdatacomReader::LoadEURUSD2014()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201401.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201402.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201403.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201404.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201405.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201406.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201407.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201408.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201409.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201410.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201411.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2014\\DAT_ASCII_EURUSD_T_201412.csv");
}

void HistdatacomReader::LoadEURUSD2015()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201501.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201502.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201503.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201504.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201505.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201506.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201507.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201508.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201509.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201510.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201511.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2015\\DAT_ASCII_EURUSD_T_201512.csv");
}

void HistdatacomReader::LoadEURUSD2016()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201601.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201602.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201603.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201604.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201605.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201606.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201607.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201608.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201609.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201610.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201611.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2016\\DAT_ASCII_EURUSD_T_201612.csv");
}


void HistdatacomReader::LoadEURUSD2017()
{
    // ************************************************************************************
    // Get history data from: /home/mihai/1TB/Documents/Trading/histdata.com/EURUSD/
    // ************************************************************************************

    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201701.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201702.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201703.csv");

    /* test with only 3 moth data
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201704.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201705.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201706.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201707.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201708.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201709.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201710.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201711.csv");
    m_offerFileVec.push_back("c:\\Users\\Mihai\\Documents\\histdata.com\\EURUSD\\DAT_ASCII_EURUSD_T_201712.csv");
    */
}

void HistdatacomReader::LoadEURUSD2018()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201801.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201802.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201803.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201804.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201805.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201806.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201807.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201808.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201809.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201810.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201811.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2018\\DAT_ASCII_EURUSD_T_201812.csv");
}

void HistdatacomReader::LoadEURUSD2019()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2019\\DAT_ASCII_EURUSD_T_201901.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2019\\DAT_ASCII_EURUSD_T_201902.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2019\\DAT_ASCII_EURUSD_T_201903.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2019\\DAT_ASCII_EURUSD_T_201904.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2019\\DAT_ASCII_EURUSD_T_201905.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2019\\DAT_ASCII_EURUSD_T_201906.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2019\\DAT_ASCII_EURUSD_T_201907.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_usd_2019\\DAT_ASCII_EURUSD_T_201908.csv");
}

void HistdatacomReader::LoadEURJPY2017()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201701_0.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201701_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201702.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201703.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201704.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201705.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201706.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201707.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201708.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201709.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201710.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201711.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\eur_jpy_2017\\DAT_ASCII_EURJPY_T_201712.csv");
}

void HistdatacomReader::LoadUSDJPY2017()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201701_0.csv"); // fast
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201701_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201701_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201702_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201702_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201703_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201703_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201704_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201704_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201705_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201705_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201706_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201706_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201707_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201707_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201708_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201708_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201709_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201709_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201710_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201710_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201711_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201711_2.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201712_1.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\usd_jpy_2017\\DAT_ASCII_USDJPY_T_201712_2.csv");
}

void HistdatacomReader::LoadGBPJPY2017()
{
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201701.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201702.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201703.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201704.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201705.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201706.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201707.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201708.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201709.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201710.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201711.csv");
    m_offerFileVec.push_back("d:\\GitHub\\histdatacom-history\\gbp_jpy_2017\\DAT_ASCII_GBPJPY_T_201712.csv");
}
