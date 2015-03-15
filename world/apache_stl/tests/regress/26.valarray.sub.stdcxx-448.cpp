/************************************************************************
 *
 * 26.valarray.sub.stdcxx-448.cpp - regression test for STDCXX-448
 *   https://issues.apache.org/jira/browse/STDCXX-448
 *
 * $Id: 26.valarray.sub.stdcxx-448.cpp 548380 2007-06-18 15:32:08Z sebor $
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
#include <valarray>


int main ()
{
    const std::valarray<double> dval;
    
    std::valarray<double> result (dval [std::gslice ()]);

    assert (result.size () == 0);

    return 0;
}
