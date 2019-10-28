/*
    Copyright (C) 2018 Mihai Vasilian

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program. If not, see http://www.gnu.org/licenses/.

    contact: grayasm@gmail.com
*/


#include "HistoryPricesReader.hpp"
#include "OHLCPrice.hpp"
#include "unistd.hpp"
#include "filename.hpp"
#include "stream.hpp"


HistoryPricesReader::HistoryPricesReader(const stl::string& instrument)
{
    m_instrument = instrument;

    m_offerFileVec.push_back("d:\\GitHub\\fxcm-history\\EUR_USD_2017.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-history\\EUR_USD_2017_1.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-history\\EUR_USD_2017_2.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-history\\EUR_USD_2017_3.txt");

    // m_offerFileVec.push_back("d:\\GitHub\\fxcm-history\\EUR_USD_2017_4_testing.txt");
    
    m_ofvPos = 0;
    // m_offersVec; - empty
    m_ovPos = 0;
}

HistoryPricesReader::~HistoryPricesReader()
{
}

bool HistoryPricesReader::GetOffer(fx::Offer& offer)
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


void HistoryPricesReader::ParseFile(const stl::string& filePath,
    stl::vector<fx::Offer>& result)
{
    sys::filename historyFile(filePath);
    if (!historyFile.access(F_OK))
        return; // error

    FILE* pf = fopen(historyFile.get_path().c_str(), "r");
    if (pf == NULL)
        return; // error

    const int bufsz = 1000000;
    char buf[bufsz];
    int bufmax = 0;
    int bufpos = 0;

    fx::OHLCPrice* hp = new fx::OHLCPrice(
        "",
        "",
        sys::time(),
        0, 0, 0, 0,
        0, 0, 0, 0,
        0);

    // some details are only for EUR/USD (for now)
    if (m_instrument != "EUR/USD")
    {
        fclose(pf);
        return;
    }

    fx::Offer offer(
        "0",
        "EUR/USD",
        5,        // precision
        0.0001, // pointSize
        sys::time(),
        0,        // bid
        0,        // ask
        0,        // vol
        true);    // trading is open
    fx::Offer offerOHLC[4] = { offer, offer, offer, offer };

    stl::string fline;
    char c;

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

            pch = strtok(str, ",=");
            while (pch != NULL)
            {
                i++;

                if (i % 2 != 0) { // One of: {I T BO BH BL BC AO AH AL AC V}
                    s1 = stl::string(pch);
                    stl::trim(s1);
                }
                else if (s1 == "I") {
                    hp->SetInstrument(pch);
                }
                else if (s1 == "T")
                {
                    //"2018-JAN-12 23:00:00"
                    int year, day, hour, min, sec;
                    char mon[5];
                    sscanf(pch, "%d-%3s-%d %d:%d:%d",
                        &year, mon, &day, &hour, &min, &sec);

                    sys::time::Month tmon;
                    if (strcmp(mon, "JAN") == 0) tmon = sys::time::JAN;
                    else if (strcmp(mon, "FEB") == 0) tmon = sys::time::FEB;
                    else if (strcmp(mon, "MAR") == 0) tmon = sys::time::MAR;
                    else if (strcmp(mon, "APR") == 0) tmon = sys::time::APR;
                    else if (strcmp(mon, "MAY") == 0) tmon = sys::time::MAY;
                    else if (strcmp(mon, "JUN") == 0) tmon = sys::time::JUN;
                    else if (strcmp(mon, "JUL") == 0) tmon = sys::time::JUL;
                    else if (strcmp(mon, "AUG") == 0) tmon = sys::time::AUG;
                    else if (strcmp(mon, "SEP") == 0) tmon = sys::time::SEP;
                    else if (strcmp(mon, "OCT") == 0) tmon = sys::time::OCT;
                    else if (strcmp(mon, "NOV") == 0) tmon = sys::time::NOV;
                    else if (strcmp(mon, "DEC") == 0) tmon = sys::time::DEC;
                    else
                        throw stl::exception("Cannot convert the month from history file");

                    sys::time hptime(year, tmon, day, hour, min, sec);
                    hp->SetTime(hptime);
                }
                else {
                    double val;
                    stl::to_value(pch, val);

                    if (s1 == "BO") hp->SetBidOpen(val);
                    else if (s1 == "BH") hp->SetBidHigh(val);
                    else if (s1 == "BL") hp->SetBidLow(val);
                    else if (s1 == "BC") hp->SetBidClose(val);
                    else if (s1 == "AO") hp->SetAskOpen(val);
                    else if (s1 == "AH") hp->SetAskHigh(val);
                    else if (s1 == "AL") hp->SetAskLow(val);
                    else if (s1 == "AC") hp->SetAskClose(val);
                    else if (s1 == "V") hp->SetVolume((int)val);
                    else
                        throw stl::exception("Cannot convert ID from history file");
                }

                pch = strtok(NULL, ",=");
            } // while(pch)

            if (m_instrument == hp->GetInstrument())
            {
                static int offerID = 0;
                offerID++;
                offer.SetOfferID(stl::from_value(offerID));
                offer.SetTime(hp->GetTime());
                offer.SetBid(hp->GetBidOpen());
                offer.SetAsk(hp->GetAskOpen());
                offer.SetVolume(hp->GetVolume() / 4);
                // Open Offer
                offerOHLC[0] = offer;                
                

                offerID++;
                offer.SetOfferID(stl::from_value(offerID));
                offer.SetTime(hp->GetTime() + 15);
                bool highFirst = (hp->GetAskOpen() > hp->GetAskClose());
                offer.SetBid(highFirst == true ? hp->GetBidHigh() : hp->GetBidLow());
                offer.SetAsk(highFirst == true ? hp->GetAskHigh() : hp->GetAskLow());
                // High Offer (if highFirst)
                offerOHLC[1] = offer;


                offerID++;
                offer.SetOfferID(stl::from_value(offerID));
                offer.SetTime(hp->GetTime() + 30);
                offer.SetBid(highFirst == true ? hp->GetBidLow() : hp->GetBidHigh());
                offer.SetAsk(highFirst == true ? hp->GetAskLow() : hp->GetAskHigh());
                // Low Offer (if highFirst)
                offerOHLC[2] = offer;
                

                offerID++;
                offer.SetOfferID(stl::from_value(offerID));
                offer.SetTime(hp->GetTime() + 45);
                offer.SetBid(hp->GetBidClose());
                offer.SetAsk(hp->GetAskClose());
                // Close Offer
                offerOHLC[3] = offer;


                Interpolate(offerOHLC[0], offerOHLC[1], result);
                Interpolate(offerOHLC[1], offerOHLC[2], result);
                Interpolate(offerOHLC[2], offerOHLC[3], result);

#ifdef DEBUG
                if (result.size() % 1000 == 0)
                    stl::cout << "fetched " << result.size() << std::endl;
#endif
            }

            fline.resize(0);
            continue;
        } // c == '\n'

        fline.append(1, c);
    }

    fclose(pf);
}


void HistoryPricesReader::Interpolate(const fx::Offer& beg, const fx::Offer& end,
    stl::vector<fx::Offer>& result)
{
    // clear result outside if needed!!

    double rate2pip = 1 / beg.GetPointSize();
    double pip2rate = beg.GetPointSize();

    double bidb = beg.GetBid();
    double bide = end.GetBid();
    double bidpips = (bide - bidb) * rate2pip;

    double askb = beg.GetAsk();
    double aske = end.GetAsk();
    double askpips = (aske - askb) * rate2pip;

    int count = (int)std::max<double>(fabs(bidpips), fabs(askpips));
    int div = (count > 0 ? count : 1);

    double vol = (beg.GetVolume() + end.GetVolume()) / (count + 1);
    sys::time tdiff = end.GetTime() - beg.GetTime();
    double secdiff =
        ((double)(tdiff.hour_() * sys::time::hourSEC +
        tdiff.min_() * sys::time::minSEC +
        tdiff.sec_())) / div;

    fx::Offer offer(beg);
    for (int i = 0; i <= count; ++i)
    {
        stl::string offerID(beg.GetOfferID());
        offerID += "-INT-";
        offerID += stl::from_value(i);
        offer.SetOfferID(offerID);
        offer.SetTime(beg.GetTime() + i * secdiff);
        offer.SetBid(beg.GetBid() + (i * bidpips / div) * pip2rate);
        offer.SetAsk(beg.GetAsk() + (i * askpips / div) * pip2rate);
        offer.SetVolume(vol);
        result.push_back(offer);
    }
}
