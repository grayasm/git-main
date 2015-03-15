/************************************************************************
*
* 21.string.find.stdcxx-1035.cpp - regression test for STDCXX-1035
*
* https://issues.apache.org/jira/browse/STDCXX-1035
*
* $Id: 21.string.find.stdcxx-1035.cpp 772572 2009-05-07 09:43:22Z faridz $
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

int main ()
{
    std::string s = ".google.com";
    std::string s1 = "www.google.google.com";

    std::string::size_type pos = s1.find (s);

    assert(10 == pos);

    return 0;
}
