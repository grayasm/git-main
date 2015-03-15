#include "stdafx.h"
#include "SessionStatusListener.h"
#include "SampleParametersHelper.h"
#include "PipCostCalculator.h"
#include "PipCostCalculatorUsageSample.h"

/** Constructor.
*/
PipCostCalculatorUsageSample::PipCostCalculatorUsageSample()
{
    mSession = NULL;
    mSessionListener = NULL;
}

/** Main method: executes the sample. 
    Returns whether the sample executed successfully.
*/
bool PipCostCalculatorUsageSample::execute(SampleParametersHelper &sampleParams)
{
    if (!login(sampleParams))
        return false;

    printPipCosts();

    logout();

    return true;
}

/** Prints the pip costs.
*/
void PipCostCalculatorUsageSample::printPipCosts()
{
    O2G2Ptr<IO2GOffersTable> offersTable = static_cast<IO2GOffersTable *>(mTableManager->getTable(Offers));
    O2G2Ptr<IO2GAccountsTable> accountsTable = static_cast<IO2GAccountsTable *>(mTableManager->getTable(Accounts));

    IO2GTableIterator it;
    IO2GOfferTableRow *row = NULL;
    PipCostCalculator calculator(mSession, offersTable, accountsTable);
    while (offersTable->getNextRow(it, row))
    {    
        O2G2Ptr<IO2GOfferTableRow> offer = (IO2GOfferTableRow*)row;
        double pipCost = calculator.calculatePipCost(offer);        
        
        std::cout << offer->getInstrument() << ": " << pipCost << std::endl;                      
    }
}


/** Creates the session and login.
*/
bool PipCostCalculatorUsageSample::login(SampleParametersHelper &sampleParameters)
{
    mSession = CO2GTransport::createSession();
    mSessionListener = new SessionStatusListener(mSession, false, sampleParameters.getParamValue("sessionid"), sampleParameters.getParamValue("pin"));
    mSession->subscribeSessionStatus(mSessionListener);

    //in this sample we use tables manager. This method must be called before logging in to ForexConnect.    
    mSession->useTableManager(Yes, NULL);   

    mSessionListener->reset();
    mSession->login(sampleParameters.getParamValue("login"), sampleParameters.getParamValue("password"),
            sampleParameters.getParamValue("url"), sampleParameters.getParamValue("connection"));    
    if (!mSessionListener->waitEvents() || !mSessionListener->isConnected())
        return false;
    mTableManager = mSession->getTableManager();
    //checks whether tables are loaded, if not, logout and return error
    while (mTableManager->getStatus() != TablesLoaded)
    {}    
    return true;
}

/** Disconnect.*/
void PipCostCalculatorUsageSample::logout()
{
    if (mSession == NULL)
        return;
    //TODO
    if (mSession->getSessionStatus() != IO2GSessionStatus::Disconnected)
    {
        mSessionListener->reset();
        mSession->logout();
        mSessionListener->waitEvents();
    }

    mSession->unsubscribeSessionStatus(mSessionListener);
    mSessionListener->release();
    mSession->release();
    
    mSession = NULL;
    mSessionListener = NULL;
}

/** Gets the last error description or NULL if no error.
*/
const char* PipCostCalculatorUsageSample::getLastError() const
{
    return mLastError.c_str();
}

/** Sets the last error.
*/
void PipCostCalculatorUsageSample::setLastError(const char *error)
{
    mLastError = error;
}
