/************************************************************************
 *
 * 18.limits.traps.stdcxx-624.cpp - regression test for STDCXX-624
 *
 * $Id: 18.limits.traps.stdcxx-624.cpp 671364 2008-06-24 22:09:44Z vitek $
 *
 ***************************************************************************
 *
 * Licensed to the Apache Software  Foundation (ASF) under one or more
 * contributor  license agreements.  See  the NOTICE  file distributed
 * with  this  work  for  additional information  regarding  copyright
 * ownership.   The ASF  licenses this  file to  you under  the Apache
 * License, Version  2.0 (the  "License"); you may  not use  this file
 * except in  compliance with the License.   You may obtain  a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the  License is distributed on an  "AS IS" BASIS,
 * WITHOUT  WARRANTIES OR CONDITIONS  OF ANY  KIND, either  express or
 * implied.   See  the License  for  the  specific language  governing
 * permissions and limitations under the License.
 * 
 **************************************************************************/

#include <cassert>   // for assert()
#include <csignal>   // for SIGFPE and signal()
#include <cstdlib>   // for strtod()
#include <limits>    // for numeric_limits


char digits[] = " +0.?23456789e+01";

volatile int  result;


extern "C" {

void handle_FPE (int)
{
    // if we get here (presumably in response to SIGFPE triggered
    // by a trap in integer arithmetic) verify that numeric_limits
    // traps is non-zero and successfuly exit the process
    assert (std::numeric_limits<int>::traps);

    std::exit (0);
}

}   // extern "C"


#ifdef _MSC_VER
   // use Structured Exception Handling to detect arithmetic exceptions
#  define TRY           __try
#  define EXCEPT(arg)   __except (arg)
#else
#  define TRY              if (1)
#  define EXCEPT(ignore)   else if (0)
#endif   // _MSC_VER


int main ()
{
    // prevent clever optimizers from figuring out that (zero == 0)
    digits [4] = '0';
    const int zero = (int)std::strtod (digits, 0);

    // compute a non-zero integer value
    digits [4] = '1';
    const int non_zero = (int)std::strtod (digits, 0);

    // set up a handler for the FPE signal only when traps is true
    // otherwise expect to be able to perform integer arithmetic
    // without a signal
    if (std::numeric_limits<int>::traps)
        std::signal (SIGFPE, handle_FPE);

    bool trapped = false;

    // if this traps (generates SIGFPE), verify (in the signal handler)
    // that integer arithmetic is expected to trap. if this doesn't trap
    // then we are either on windows, or traps are disabled.
    TRY {
        result  = non_zero / zero;
        result += non_zero % zero;
    }
    EXCEPT (1) {
        // windows structured exception caught
        trapped = true;
    }

    // if we get this far, verify that we have caught a structured
    // exception or integer arithmetic is known not to trap
    assert (trapped == std::numeric_limits<int>::traps);

    (void)&result;

    return 0;
}
