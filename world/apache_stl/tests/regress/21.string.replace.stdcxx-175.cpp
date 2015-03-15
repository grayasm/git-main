/************************************************************************
*
* 21.string.replace.stdcxx-175.cpp - test case from STDCXX-175 issue
*
* $Id: 21.string.replace.stdcxx-175.cpp 814419 2009-09-13 22:46:50Z sebor $
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

#include <cassert>
#include <string>
#include <stdexcept>

int main ()
{
    std::string s (4095, 'a');

    try {
        s.replace (0, 1, "a", s.max_size () + 1);
        assert (!"Expect length error, got nothing");
    }
    catch (std::length_error&) {
    }

    return 0;
}
