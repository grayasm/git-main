#pragma once

/** Description of the single commission.
*/
class IO2GCommissionDescription : public IAddRef
{
protected:

    IO2GCommissionDescription(){};

public:

    virtual O2GCommissionStage getStage() = 0;

    virtual O2GCommissionUnitType getUnitType() = 0;
    
    virtual double getCommissionValue() = 0;

    virtual double getMinCommission() = 0;
};

class IO2GCommissionDescriptionsCollection : public IAddRef
{
protected:

    IO2GCommissionDescriptionsCollection(){};

public:

    virtual int size() = 0;

    virtual IO2GCommissionDescription* get(int i) = 0;
};

class IO2GCommissionProviderListener : public IAddRef
{
public:

    virtual void onChangeCommissionProviderStatus(O2GCommissionStatus status) = 0;

    virtual void onNeedUpdateCommissions() = 0;
};

/** Main commission interface (used to access all commissions related information).*/
class IO2GCommissionsProvider : public IAddRef
{
 protected:
    IO2GCommissionsProvider(){};
 public:

    /** Gets condition distance for the stop. */
    virtual IO2GCommissionDescriptionsCollection* getCommissionDescriptions(const char* offerID, const char* atpID) = 0;    

    /** Gets the current status. */
    virtual O2GCommissionStatus getStatus() = 0;
    virtual void subscribe(IO2GCommissionProviderListener *listener) = 0;
    virtual void unsubscribe(IO2GCommissionProviderListener *listener) = 0;

    //Methoods to calculte commissions
    virtual double calcOpenCommission(IO2GOfferRow* offer, IO2GAccountRow* account, int amount, const char* buySell, double rate) = 0;
    virtual double calcCloseCommission(IO2GOfferRow* offer, IO2GAccountRow* account, int amount, const char* buySell, double rate) = 0;
    virtual double calcTotalCommission(IO2GOfferRow* offer, IO2GAccountRow* account, int amount, const char* buySell, double rateOpen, double rateClose) = 0;
};

