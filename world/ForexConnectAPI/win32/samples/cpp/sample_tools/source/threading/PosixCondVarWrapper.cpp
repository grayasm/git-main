#include "stdafx.h"

#include <pthread.h>
#include <sample_tools.h>
#include "threading/PosixCondVarWrapper.h"

PosixCondVar::PosixCondVar()
    : mRefCounter(1), mIsSignaled(false)
{
    pthread_cond_init(&mCondVar, NULL);
    pthread_mutex_init(&mCondMutex, NULL);
}

PosixCondVar::~PosixCondVar()
{
    pthread_cond_destroy(&mCondVar);
    pthread_mutex_destroy(&mCondMutex);
}

pthread_cond_t &PosixCondVar::getCondVar()
{
    return mCondVar;
}

pthread_mutex_t &PosixCondVar::getMutex()
{
    return mCondMutex;
}

void PosixCondVar::addRef()
{
    InterlockedIncrement(&mRefCounter);
}

void PosixCondVar::release()
{
    if (!InterlockedDecrement(&mRefCounter))
        delete this;
}
