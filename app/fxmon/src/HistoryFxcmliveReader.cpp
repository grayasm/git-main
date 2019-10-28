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

#include "HistoryFxcmliveReader.hpp"
#include "unistd.hpp"
#include "filename.hpp"
#include "stream.hpp"


HistoryFxcmliveReader::HistoryFxcmliveReader(const stl::string& instrument)
{
    m_instrument = instrument;

    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_01_28_23_06_21.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_01_29_09_34_38.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_01_29_18_10_47.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_01_30_06_25_41.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_01_30_15_28_04.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_01_31_02_38_00.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_01_31_12_48_19.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_01_31_20_58_26.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_01_09_39_17.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_01_17_57_54.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_02_05_01_58.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_02_14_48_53.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_04_22_45_41.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_05_09_12_33.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_05_17_22_37.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_06_01_34_38.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_06_08_21_48.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_06_15_12_35.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_06_22_10_50.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_07_08_35_18.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_07_16_26_38.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_08_00_52_15.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_08_09_13_24.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_08_10_52_10.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_08_18_11_10.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_09_02_44_08.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_09_11_40_19.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_09_18_21_58.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_11_22_05_48.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_12_09_32_01.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_12_17_28_25.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_13_05_18_36.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_13_14_10_00.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_14_00_30_40.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_14_10_44_05.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_14_18_48_08.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_15_05_31_46.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_15_14_12_59.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_15_22_40_34.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_16_09_46_05.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_16_17_31_18.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_18_22_06_08.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_19_11_17_55.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_20_02_33_26.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_20_13_39_09.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_21_00_20_01.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_21_11_49_12.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_21_20_12_52.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_22_08_31_56.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_22_17_24_52.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_23_06_20_51.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_23_16_14_04.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_25_22_05_04.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_26_09_45_09.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_26_19_43_22.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_27_09_14_23.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_27_18_36_56.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_28_07_09_13.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_02_28_16_23_56.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_01_05_01_12.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_01_15_47_38.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_02_01_55_28.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_02_13_17_17.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_02_21_46_47.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_04_22_04_43.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_05_08_28_30.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_05_15_46_36.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_06_01_47_59.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_06_11_52_17.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_06_18_13_45.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_07_04_13_05.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_07_13_01_53.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_07_19_37_40.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_08_08_00_10.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_08_15_06_50.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_08_23_36_58.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_09_10_24_19.txt");
    m_offerFileVec.push_back("d:\\GitHub\\fxcm-offers\\Offers_2018_03_09_17_02_12.txt");

    
    m_ofvPos = 0;
    // m_offersVec; - empty
    m_ovPos = 0;
}

HistoryFxcmliveReader::~HistoryFxcmliveReader()
{
}
    
bool HistoryFxcmliveReader::GetOffer(fx::Offer& offer)
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


void HistoryFxcmliveReader::ParseFile(const stl::string& filePath,
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
    
    fx::Offer offer;
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

                if (i % 2 != 0) { // One of: {Id I Pr T PS B A Vol}
                    s1 = stl::string(pch);
                    stl::trim(s1);
                }
                else if (s1 == "Id") {
                    offer.SetOfferID(pch);
                }
                else if (s1 == "I") {
                    offer.SetInstrument(pch);

                    // break early
                    if (m_instrument != offer.GetInstrument())
                        break; // while(pch!=NULL) {...}
                }
                else if (s1 == "Pr") {
                    double val;
                    stl::to_value(pch, val);
                    offer.SetPrecision(val);
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

                    sys::time timeval(year, tmon, day, hour, min, sec);
                    offer.SetTime(timeval);
                }
                else if (s1 == "PS") {
                    double val;
                    stl::to_value(pch, val);
                    offer.SetPointSize(val);
                }
                else if (s1 == "B") {
                    double val;
                    stl::to_value(pch, val);
                    offer.SetBid(val);
                }
                else if (s1 == "A") {
                    double val;
                    stl::to_value(pch, val);
                    offer.SetAsk(val);
                }
                else if (s1 == "Vol") {
                    double val;
                    stl::to_value(pch, val);
                    offer.SetVolume(val);
                }

                pch = strtok(NULL, ",=");
            } // while(pch)

            if (m_instrument == offer.GetInstrument())
            {
                result.push_back(offer);

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
