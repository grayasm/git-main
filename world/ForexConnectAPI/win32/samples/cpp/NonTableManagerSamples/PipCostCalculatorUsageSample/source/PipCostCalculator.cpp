#include "stdafx.h"
#include "SessionStatusListener.h"
#include "SampleParametersHelper.h"
#include "PipCostCalculator.h"

/** Constructor.
    Calculates some values common for all offers.
*/
PipCostCalculator::PipCostCalculator(IO2GSession *session, IO2GOffersTable *offersTable, IO2GAccountsTable *accountsTable)
{
    mSession = session;
    mOffersTable = offersTable;
    mAccountsTable = accountsTable;

    mAccountCurrency = getAccountCurrency();
}

double PipCostCalculator::calculatePipCost(IO2GOfferRow *offer)
{     
    // is it FOREX or CFD instrument? 
    bool isForexInstrument = (offer->getInstrumentType() == 1);

    //min BaseUnitSize
    int minBaseUnitSize = calcMinBaseUnitSize(offer);

    // Get contractMultiplier.    
    double contractMultiplier = offer->getContractMultiplier() * minBaseUnitSize;
    
    // Set base value for Pip Cost.
    double pipCost = contractMultiplier * offer->getPointSize();
    double pipCostBid = pipCost;
    double pipCostAsk = pipCost;

    // local copy of Offer's Instrument (currency pair).
    char copy_offerInstrument[32];
    const char *offerInstrument = offer->getInstrument();
    unsigned strLength = (unsigned)(strrchr(offerInstrument, 0) - offerInstrument);
    memcpy_s(copy_offerInstrument, sizeof(copy_offerInstrument), offerInstrument, strLength + 1);

    // Get Quote part (XXX/Quote) from Offer's Instrument (currency pair).
    // *** for common CFD instruments the '/' delimiter is absent, so use Offer's ContractCurrency field as quote currency part. ***
    char *slashPlace = (char *)memchr(copy_offerInstrument, '/', strLength);
    const char *quoteCurrency = (slashPlace != NULL ? slashPlace + 1 : offer->getContractCurrency());

    // Get Base part (Base/XXX) from Offer's Instrument (currency pair).
    if (slashPlace != NULL) *slashPlace = 0;
    const char *baseCurrency = copy_offerInstrument;

    // Main calculation algorithm.

    // Get Account Currency.    
    const char *accountCurrency = mAccountCurrency.c_str();

    int crossType = -1;

    // Detect and process "Direct Case" (most often)
    // If Account Currency is equal to 'quote' part (XXX/Quote) of Offer's Instrument (currency pair).
    if (!memcmp(accountCurrency, quoteCurrency, 3))
    {
        // already calculated as base value (see above).
       crossType = 0;
    }
    // Detect and process "Indirect Case"
    // If Account Currency is equal to 'base' part (Base/XXX) of Offer's Instrument (currency pair).
    // check this case only for Forex's instruments. 
    else if (isForexInstrument && !memcmp(accountCurrency, baseCurrency, 3))
    {
        double averageRate = (offer->getAsk() + offer->getBid()) / 2;

        pipCostBid = pipCost / offer->getBid();
        pipCostAsk = pipCost / offer->getAsk();
        pipCost /= averageRate;

        crossType = 1;
    }
    // Detect and process "Cross Case"
    // If Account Currency is not equal to 'base' and 'quote' parts (Base/Quote) of Offer's Instrument (currency pair),
    else
    {
        char pairCombination[] = "XXX/XXX";

        // try to get and use rate relative to the Quote currency.
        memcpy_s(pairCombination, sizeof(pairCombination), quoteCurrency, 3);
        memcpy_s(pairCombination + 4, sizeof(pairCombination) - 4 * sizeof(char), accountCurrency, 3);  // for 'quoted account's currency' combination.

        if (getConversionRate(pairCombination, true, pipCost))
            crossType = 2;
        else
        {
            memcpy_s(pairCombination, sizeof(pairCombination), accountCurrency, 3); // for 'based account's currency' combination.
            memcpy_s(pairCombination + 4, sizeof(pairCombination) - 4 * sizeof(char), quoteCurrency, 3);

            if (getConversionRate(pairCombination, false, pipCost))
                crossType = 2;
            else
            {   // try to get and use rate relative to the Base currency.
                memcpy_s(pairCombination, sizeof(pairCombination), baseCurrency, 3);
                memcpy_s(pairCombination + 4, sizeof(pairCombination) - 4 * sizeof(char), accountCurrency, 3); //  for 'quoted account's currency' combination.

                if (getConversionRate(pairCombination, true, pipCost))
                {
                    double averageRate = (offer->getAsk() + offer->getBid()) / 2;

                    pipCostBid = pipCost / offer->getBid();
                    pipCostAsk = pipCost / offer->getAsk();
                    pipCost /= averageRate;

                    crossType = 3;
                }
                else
                {
                    memcpy_s(pairCombination, sizeof(pairCombination), accountCurrency, 3); // for 'based account's currency' combination.
                    memcpy_s(pairCombination + 4, sizeof(pairCombination) - 4 * sizeof(char), baseCurrency, 3);

                    if (getConversionRate(pairCombination, false, pipCost))
                    {
                        double averageRate = (offer->getAsk() + offer->getBid()) / 2;

                        pipCostBid = pipCost / offer->getBid();
                        pipCostAsk = pipCost / offer->getAsk();
                        pipCost /= averageRate;

                        crossType = 3;
                    }
                    else
                    {   // try to get and use rate via 'major currency (USD)' relative to the Quote currency.
                        if (getConversionRateByMajor(quoteCurrency, "USD", accountCurrency, pipCost))
                            crossType = 4;
                        else
                        {   // try to get and use rate via 'major currency (EUR)' relative to the Quote currency.
                            if (getConversionRateByMajor(quoteCurrency, "EUR", accountCurrency, pipCost))
                                crossType = 4;
                            else                            
                                crossType = -1; // Set to undetected cross type.                            
                        }
                    }
                }
            }
        }
    }    

    return pipCost;
}

bool PipCostCalculator::getConversionRate(const char *pairCombination, bool isQuotedByAccountCurrency, double &pipCost)
{
    bool rc = false;


    IO2GTableIterator it;
    IO2GRow *row;
    if (!mOffersTable->getNextGenericRowByColumnValue("Instrument", pairCombination, it, row))
        return false;
    O2G2Ptr<IO2GOfferRow> offerRow = (IO2GOfferRow*)row;    
    double averageRate = (offerRow->getAsk() + offerRow->getBid()) / 2;
    if (isQuotedByAccountCurrency)
        pipCost *= averageRate;
    else
        pipCost /= averageRate;            
    return true;        
}

bool PipCostCalculator::getConversionRateByMajor(const char *currency, const char *majorCurrency, const char *accountCurrency, double &pipCost)
{
    bool rc = false;

    double _pipCost = pipCost;

    char pairCombination[] = "XXX/XXX";
    char pairCombinationMajor[] = "XXX/XXX";

    memcpy_s(pairCombinationMajor, sizeof(pairCombinationMajor), currency, 3);
    memcpy_s(pairCombinationMajor + 4, sizeof(pairCombinationMajor) - 4 * sizeof(char),  majorCurrency, 3);

    if (getConversionRate(pairCombinationMajor, true, _pipCost))
    {
        memcpy_s(pairCombination, sizeof(pairCombinationMajor), majorCurrency, 3);
        memcpy_s(pairCombination + 4, sizeof(pairCombinationMajor) - 4 * sizeof(char), accountCurrency, 3);

        if (getConversionRate(pairCombination, true, _pipCost))
            rc = true;
        else
        {
            memcpy_s(pairCombination, sizeof(pairCombinationMajor), accountCurrency, 3);
            memcpy_s(pairCombination + 4, sizeof(pairCombinationMajor) - 4 * sizeof(char), majorCurrency, 3);

            if (getConversionRate(pairCombination, false, _pipCost))
                rc = true;
        }
    }
    else
    {
        memcpy_s(pairCombinationMajor, sizeof(pairCombinationMajor), majorCurrency, 3);
        memcpy_s(pairCombinationMajor + 4, sizeof(pairCombinationMajor) - 4 * sizeof(char), currency, 3);

        if (getConversionRate(pairCombinationMajor, false, _pipCost))
        {
            memcpy_s(pairCombination, sizeof(pairCombinationMajor), majorCurrency, 3);
            memcpy_s(pairCombination + 4, sizeof(pairCombinationMajor) - 4 * sizeof(char), accountCurrency, 3);

            if (getConversionRate(pairCombination, true, _pipCost))
                rc = true;
            else
            {
                memcpy_s(pairCombination, sizeof(pairCombinationMajor), accountCurrency, 3);
                memcpy_s(pairCombination + 4, sizeof(pairCombinationMajor) - 4 * sizeof(char), majorCurrency, 3);

                if (getConversionRate(pairCombination, false, _pipCost))
                    rc = true;
            }
        }
    }

    if (rc)
        pipCost = _pipCost;

    return rc;
}

std::string PipCostCalculator::getAccountCurrency()
{
    O2G2Ptr<IO2GLoginRules> loginRules = mSession->getLoginRules();
    O2G2Ptr<IO2GResponse> response = loginRules->getSystemPropertiesResponse();
    O2G2Ptr<IO2GResponseReaderFactory> factory = mSession->getResponseReaderFactory();
    O2G2Ptr<IO2GSystemPropertiesReader> systemResponseReader = factory->createSystemPropertiesReader(response);
    return systemResponseReader->findProperty("BASE_CRNCY");    
}

/** Calculates BaseUnitSize (as Mininum value from all pAccount->getBaseUnitSize())*/
int PipCostCalculator::calcMinBaseUnitSize(IO2GOfferRow *offer)
{    
    O2G2Ptr<IO2GLoginRules> loginRules = mSession->getLoginRules();
    O2G2Ptr<IO2GTradingSettingsProvider> tradingSettingsProvider = loginRules->getTradingSettingsProvider();
    IO2GAccountTableRow *account = NULL;
    IO2GTableIterator iterator;

    int minBaseUnitSize = 0;
    while (mAccountsTable->getNextRow(iterator, account))
    {        
        int accountBaseUnitSize = tradingSettingsProvider->getBaseUnitSize(offer->getInstrument(), account);
        if (minBaseUnitSize == 0 || minBaseUnitSize > accountBaseUnitSize)
            minBaseUnitSize = accountBaseUnitSize; // set current Mininum.

        account->release();
    }        
    return minBaseUnitSize;
}