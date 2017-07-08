#pragma once

class Order2Go2 IO2GLevel2MarketDataUpdatesReader : public IAddRef
{
 protected:
    IO2GLevel2MarketDataUpdatesReader();
 public:
     virtual int getPriceQuotesCount() = 0;
     virtual double getDateTime(int quoteIdx) = 0;
     virtual int getSymbolID(int quoteIdx) = 0;
     virtual int getVolume(int quoteIdx) = 0;

     virtual int getPricesCount(int quoteIdx) = 0;
     virtual bool isBid(int quoteIdx, int priceIdx) = 0;
     virtual bool isAsk(int quoteIdx, int priceIdx) = 0;
     virtual bool isLow(int quoteIdx, int priceIdx) = 0;
     virtual bool isHigh(int quoteIdx, int priceIdx) = 0;
     virtual double getRate(int quoteIdx, int priceIdx) = 0;
     virtual double getAmount(int quoteIdx, int priceIdx) = 0;
     virtual const char *getCondition(int quoteIdx, int priceIdx) = 0;
     virtual const char *getOriginator(int quoteIdx, int priceIdx) = 0;
};

