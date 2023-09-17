/*
Copyright (C) 2014 Mihai Vasilian
*/



//c
#include <stdlib.h>
#include <stdio.h>
#include <exception>

//c++
// local
#include "Test.hpp"
#include "HistoryPricesGetter.hpp"
#include "RealEngine.hpp"
#include "TestEngine.hpp"
#include "OMPEngine.hpp"



int main(int /*argc*/, char** /*argv*/)
{
    // disable stdout buffer
    setvbuf(stdout, NULL, _IONBF, 0);

    // GetHistoryPrices();
    // LoadHistoryPrices();
    // RealEngine();
    // TestEngine();
    // OMPEngine();
    test4();
    // test12();
    // test13();
    // test14();
    // test15();
    // test16();
    // test17();
    // test18();

    return 0;
}
