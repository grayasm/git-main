#pragma once

/* All interfaces and classes of HistoricalPriceAPI reside in pricehistorymgr namespace. */
namespace pricehistorymgr
{

class CThreadSafeAddRefImpl
{
 public:
    CThreadSafeAddRefImpl()
    {
        m_dwRef = 1;
    }
    virtual ~CThreadSafeAddRefImpl(){};

    long internalAddRef()
    {
        return ++m_dwRef;
    }

    long internalRelease()
    {
        long lResult = --m_dwRef;
        if (lResult == 0)
            delete this;
        return lResult;
    }
 private:
    volatile std::atomic_long m_dwRef{ 0 };
};

template<typename T> class TThreadSafeAddRefImpl : public T
{
 public:
    TThreadSafeAddRefImpl()
    {
        m_dwRef = 1;
    }
    virtual ~TThreadSafeAddRefImpl(){};

    long addRef()
    {
        return ++m_dwRef;
    }
    long release()
    {
        long lResult = --m_dwRef;
        if (lResult == 0)
            delete this;
        return lResult;
    }
 private:
     volatile std::atomic_long m_dwRef{ 0 };
};

}
