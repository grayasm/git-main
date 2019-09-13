#pragma once

class Order2Go2 O2GAtomic
{
 public:
    static unsigned int InterlockedInc(volatile unsigned int &dwRef);
    static unsigned int InterlockedDec(volatile unsigned int &dwRef);
};
