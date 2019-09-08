#pragma once

#include "IAddRef.h"
#include "O2GEnum.h"

class IO2GOfferRow;
class IO2GAccountRow;
class IO2GRolloverProviderListener;
class IO2GRolloverDisplayUpdateListener;

/**Rollover provider listener status changed
*/
class IO2GRolloverProviderListener
{
public:
    virtual void onStatusChanged(::O2GRolloverStatus status) = 0;
};

/** Main rollover interface (used to access all rollover related information).*/
class IO2GRolloverProvider : public IAddRef
{
 protected:
    IO2GRolloverProvider(){};
 public:

    virtual double getRolloverBuy(IO2GOfferRow* offer, IO2GAccountRow* account) = 0;

    virtual double getRolloverSell(IO2GOfferRow* offer, IO2GAccountRow* account) = 0;

    virtual O2GRolloverStatus getStatus() = 0;

    virtual void subscribe(IO2GRolloverProviderListener *listener) = 0;

    virtual void unsubscribe(IO2GRolloverProviderListener *listener) = 0;

    virtual void refreshRolloverProfiles() = 0;
};