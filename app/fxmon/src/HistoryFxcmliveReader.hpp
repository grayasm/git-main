/*
Copyright (C) 2018 Mihai Vasilian
*/

#ifndef __HistoryFxcmliveReader_hpp__
#define __HistoryFxcmliveReader_hpp__

#include "vector.hpp"
#include "string.hpp"
#include "Offer.hpp"

class HistoryFxcmliveReader
{
public:
    HistoryFxcmliveReader(const stl::string& instrument);
    ~HistoryFxcmliveReader();
    HistoryFxcmliveReader(const HistoryFxcmliveReader&) = delete;
    HistoryFxcmliveReader& operator=(const HistoryFxcmliveReader&) = delete;

    // return all recorded offers in receiving order; false if at the end;
    bool GetOffer(fx::Offer& offer);


private:
    void ParseFile(const stl::string& filePath,
        stl::vector<fx::Offer>& result);

private:
    stl::string                 m_instrument;
    stl::vector<stl::string>    m_offerFileVec;
    int                         m_ofvPos;
    stl::vector<fx::Offer>      m_offersVec;
    int                         m_ovPos;
};

#endif // __HistoryFxcmliveReader_hpp__
