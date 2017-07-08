#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include <libkern/OSAtomic.h>
#endif

namespace O2G2
{
    template<typename T> class TO2G2ThreadSafeAddRefImpl : public T
    {
     public:
        TO2G2ThreadSafeAddRefImpl()
        {
            m_dwRef = 1;
        }
        virtual ~TO2G2ThreadSafeAddRefImpl(){};

        long addRef()
        {
            #ifdef WIN32
                return InterlockedIncrement(&m_dwRef);
            #elif defined(__APPLE__) && defined(__MACH__)
                #ifdef __LP64__
                    return (long)OSAtomicIncrement64((volatile int64_t *)&m_dwRef);
                #else
                    return (long)OSAtomicIncrement32((volatile int32_t *)&m_dwRef);
                #endif
            #else  // linux and similar
                return (long)__sync_add_and_fetch(&m_dwRef, 1L);
            #endif
        }
        
        long release()
        {
            long lResult;
            #ifdef WIN32
                lResult = InterlockedDecrement(&m_dwRef);
            #elif defined(__APPLE__) && defined(__MACH__)
                #ifdef __LP64__
                    lResult = (long)OSAtomicDecrement64((volatile int64_t *)&m_dwRef);
                #else
                    lResult = (long)OSAtomicDecrement32((volatile int32_t *)&m_dwRef);
                #endif
            #else  // linux and similar
                lResult = (long)__sync_add_and_fetch(&m_dwRef, -1L);
            #endif
            if (lResult == 0)
                delete this;
            return lResult;
        }
        
     private:
        volatile long m_dwRef;
    };
}
