#include "stdafx.h"
#include <math.h>

#include <sstream>
#include <iomanip>
#include "Offer.h"
#include "ResponseListener.h"

ResponseListener::ResponseListener(IO2GSession *session)
{
    mSession = session;
    mSession->addRef();
    mRefCount = 1;
    mResponseEvent = CreateEvent(0, FALSE, FALSE, 0);
    mRequestID = "";
    mInstrument = "";
    mResponse = NULL;
    mOffers = new OfferCollection();
    std::cout.precision(2);
}

ResponseListener::~ResponseListener()
{
    if (mResponse)
        mResponse->release();
    delete mOffers;
    mSession->release();
    CloseHandle(mResponseEvent);
}

/** Increase reference counter. */
long ResponseListener::addRef()
{
    return InterlockedIncrement(&mRefCount);
}

/** Decrease reference counter. */
long ResponseListener::release()
{
    long rc = InterlockedDecrement(&mRefCount);
    if (rc == 0)
        delete this;
    return rc;
}

/** Set request. */
void ResponseListener::setRequestID(const char *sRequestID)
{
    mRequestID = sRequestID;
    if (mResponse)
    {
        mResponse->release();
        mResponse = NULL;
    }
    ResetEvent(mResponseEvent);
}

void ResponseListener::setInstrument(const char *sInstrument)
{
    mInstrument = sInstrument;
}

bool ResponseListener::waitEvents()
{
    return WaitForSingleObject(mResponseEvent, _TIMEOUT) == 0;
}

/** Gets response.*/
IO2GResponse *ResponseListener::getResponse()
{
    if (mResponse)
        mResponse->addRef();
    return mResponse;
}

/** Request execution completed data handler. */
void ResponseListener::onRequestCompleted(const char *requestId, IO2GResponse *response)
{
    if (response && mRequestID == requestId)
    {
        mResponse = response;
        mResponse->addRef();
        if (response->getType() != CreateOrderResponse)
            SetEvent(mResponseEvent);
    }
}

/** Request execution failed data handler. */
void ResponseListener::onRequestFailed(const char *requestId , const char *error)
{
    if (mRequestID == requestId)
    {
        std::cout << "The request has been failed. ID: " << requestId << " : " << error << std::endl;
        SetEvent(mResponseEvent);
    }
}

/** Request update data received data handler. */
void ResponseListener::onTablesUpdates(IO2GResponse *data)
{
    if (data)
    {
        if (data->getType() == TablesUpdates)
            printOffers(mSession, data, mInstrument.c_str());
    }
}

// Store offers data from response and print it
void ResponseListener::printOffers(IO2GSession *session, IO2GResponse *response, const char *sInstrument)
{
    O2G2Ptr<IO2GResponseReaderFactory> readerFactory = session->getResponseReaderFactory();
    if (!readerFactory)
    {
        std::cout << "Cannot create response reader factory" << std::endl;
        return;
    }
    O2G2Ptr<IO2GOffersTableResponseReader> responseReader = readerFactory->createOffersTableReader(response);
    for (int i = 0; i < responseReader->size(); ++i)
    {
        O2G2Ptr<IO2GOfferRow> offerRow = responseReader->getRow(i);
        Offer *offer = mOffers->findOffer(offerRow->getOfferID());
        if (offer)
        {
            if (offerRow->isTimeValid() && offerRow->isBidValid() && offerRow->isAskValid())
            {
                offer->setDate(offerRow->getTime());
                offer->setBid(offerRow->getBid());
                offer->setAsk(offerRow->getAsk());
            }
        }
        else
        {
            offer = new Offer(offerRow->getOfferID(), offerRow->getInstrument(),
                     offerRow->getDigits(), offerRow->getPointSize(), offerRow->getTime(),
                     offerRow->getBid(), offerRow->getAsk());
            mOffers->addOffer(offer);
        }
        if (!sInstrument || strlen(sInstrument) == 0 || strcmp(offerRow->getInstrument(), sInstrument) == 0)
        {
            std::cout << offer->getID() << ", " << offer->getInstrument() << ", "
                    << "Bid=" << std::fixed << offer->getBid() << ", "
                    << "Ask=" << std::fixed << offer->getAsk() << std::endl;
        }
    }
}

