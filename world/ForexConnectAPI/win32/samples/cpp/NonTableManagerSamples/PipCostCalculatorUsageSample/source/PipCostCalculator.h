#pragma once

class PipCostCalculator
{
public:
    
    /** Constructor.
        Calculates some values common for all offers.
    */
    PipCostCalculator(IO2GSession *session, IO2GOffersTable *offersTable, IO2GAccountsTable *accountsTable);

    /** The main calculation method.
    */
    double calculatePipCost(IO2GOfferRow *offer);

private:

    
    /** Calculates BaseUnitSize (as Mininum value from all pAccount->getBaseUnitSize())*/
    int calcMinBaseUnitSize(IO2GOfferRow *offer);       
    bool getConversionRate(const char *pairCombination, bool isQuotedByAccountCurrency, double &pipCost);
    bool getConversionRateByMajor(const char *currency, const char *majorCurrency, const char *accountCurrency, double &pipCost);
    /** Gets the account curency from the system property */
    std::string getAccountCurrency();

    IO2GSession* mSession;
    IO2GOffersTable* mOffersTable;
    IO2GAccountsTable* mAccountsTable;

    std::string mAccountCurrency;
};

