
/*
    !!! Caution:
    Do not change anything in this source code because it was automatically generated
    from XML class description
*/
#pragma once

class IO2GOfferRow : public IO2GRow
{
 protected:
    IO2GOfferRow();
  
 public:

    
    virtual const char* getOfferID() = 0;
    virtual const char* getInstrument() = 0;
    virtual const char* getQuoteID() = 0;
    virtual double getBid() = 0;
    virtual double getAsk() = 0;
    virtual double getLow() = 0;
    virtual double getHigh() = 0;
    virtual int getVolume() = 0;
    virtual DATE getTime() = 0;
    virtual const char* getBidTradable() = 0;
    virtual const char* getAskTradable() = 0;
    virtual double getSellInterest() = 0;
    virtual double getBuyInterest() = 0;
    virtual const char* getContractCurrency() = 0;
    virtual int getDigits() = 0;
    virtual double getPointSize() = 0;
    virtual const char* getSubscriptionStatus() = 0;
    virtual int getInstrumentType() = 0;
    virtual double getContractMultiplier() = 0;
    virtual const char* getTradingStatus() = 0;
    virtual const char* getValueDate() = 0;
    virtual const char* getBidID() = 0;
    virtual const char* getAskID() = 0;
    virtual DATE getBidExpireDate() = 0;
    virtual DATE getAskExpireDate() = 0;
    //

    virtual bool isOfferIDValid() = 0;
    virtual bool isInstrumentValid() = 0;
    virtual bool isQuoteIDValid() = 0;
    virtual bool isBidValid() = 0;
    virtual bool isAskValid() = 0;
    virtual bool isLowValid() = 0;
    virtual bool isHighValid() = 0;
    virtual bool isVolumeValid() = 0;
    virtual bool isTimeValid() = 0;
    virtual bool isBidTradableValid() = 0;
    virtual bool isAskTradableValid() = 0;
    virtual bool isSellInterestValid() = 0;
    virtual bool isBuyInterestValid() = 0;
    virtual bool isContractCurrencyValid() = 0;
    virtual bool isDigitsValid() = 0;
    virtual bool isPointSizeValid() = 0;
    virtual bool isSubscriptionStatusValid() = 0;
    virtual bool isInstrumentTypeValid() = 0;
    virtual bool isContractMultiplierValid() = 0;
    virtual bool isTradingStatusValid() = 0;
    virtual bool isValueDateValid() = 0;
    virtual bool isBidIDValid() = 0;
    virtual bool isAskIDValid() = 0;
    virtual bool isBidExpireDateValid() = 0;
    virtual bool isAskExpireDateValid() = 0;
};


class IO2GOfferTableRow : public IO2GOfferRow
{
 protected:
    IO2GOfferTableRow();

 public:
    
    virtual double getPipCost() = 0;
    virtual int getBidChangeDirection() = 0;
    virtual int getAskChangeDirection() = 0;
    virtual int getHiChangeDirection() = 0;
    virtual int getLowChangeDirection() = 0;
    virtual int getDefaultSortOrder() = 0;
    virtual int getFractionalPipSize() = 0;
    //

    virtual bool isBidChangeDirectionValid() = 0;
    virtual bool isAskChangeDirectionValid() = 0;
    virtual bool isHiChangeDirectionValid() = 0;
    virtual bool isLowChangeDirectionValid() = 0;
    virtual bool isDefaultSortOrderValid() = 0;
    virtual bool isFractionalPipSizeValid() = 0;
};

