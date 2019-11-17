/*
  Copyright (C) 2014 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
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
    test12();
    // test13();
    // test14();
    // test15();
    // test16();
    // test17();
    // test18();

    return 0;
}
