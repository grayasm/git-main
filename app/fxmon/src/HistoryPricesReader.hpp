/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __HistoryPricesReader_hpp__
#define __HistoryPricesReader_hpp__

#include "vector.hpp"
#include "string.hpp"
#include "Offer.hpp"

class HistoryPricesReader
{
public:
    HistoryPricesReader(const stl::string& instrument);
    ~HistoryPricesReader();
    HistoryPricesReader(const HistoryPricesReader&) = delete;
    HistoryPricesReader& operator=(const HistoryPricesReader&) = delete;

    // return all recorded offers in receiving order; false if at the end;
    bool GetOffer(fx::Offer& offer);


private:
    void ParseFile(const stl::string& filePath,
        stl::vector<fx::Offer>& result);
    void Interpolate(const fx::Offer& beg, const fx::Offer& end,
        stl::vector<fx::Offer>& result);

private:
    stl::string                 m_instrument;
    stl::vector<stl::string>    m_offerFileVec;
    int                         m_ofvPos;
    stl::vector<fx::Offer>      m_offersVec;
    int                         m_ovPos;
};

#endif // __HistoryPricesReader_hpp__
