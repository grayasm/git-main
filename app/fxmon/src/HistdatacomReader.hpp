/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __HistdatacomReader_hpp__
#define __HistdatacomReader_hpp__

#include "vector.hpp"
#include "string.hpp"
#include "Offer.hpp"

class HistdatacomReader
{
public:
    HistdatacomReader(const fx::Offer& offer, int year);
    ~HistdatacomReader();
    HistdatacomReader(const HistdatacomReader&) = delete;
    HistdatacomReader& operator=(const HistdatacomReader&) = delete;

    // return all recorded offers in receiving order; false if at the end;
    bool GetOffer(fx::Offer& offer);


private:
    void ParseFile(
        const stl::string& filePath,
        stl::vector<fx::Offer>& result);

    void LoadEURUSD1900();
    void LoadEURUSD2008();
    void LoadEURUSD2014();
    void LoadEURUSD2015();
    void LoadEURUSD2016();
    void LoadEURUSD2017();
    void LoadEURUSD2018();
    void LoadEURUSD2019();
    void LoadEURJPY2017();
    void LoadUSDJPY2017();
    void LoadGBPJPY2017();


private:
    fx::Offer                   m_offer;
    int                         m_year;
    stl::vector<stl::string>    m_offerFileVec;
    int                         m_ofvPos;
    stl::vector<fx::Offer>      m_offersVec;
    int                         m_ovPos;
};

#endif // __HistdatacomReader_hpp__
