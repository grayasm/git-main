#pragma once

class PosixCondVar
{
 public:
    PosixCondVar();

    pthread_cond_t &getCondVar();
    pthread_mutex_t &getMutex();

    void addRef();
    void release();

    volatile bool mIsSignaled;

 private:
    ~PosixCondVar();

 private:
    PosixCondVar(PosixCondVar const &);
    PosixCondVar &operator=(PosixCondVar const&);

 private:
    volatile long mRefCounter;
    pthread_cond_t mCondVar;
    pthread_mutex_t mCondMutex;
};
