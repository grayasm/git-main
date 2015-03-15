/************************************************************************
 *
 * 23.vector.cons.stdcxx-294.cpp - regression test for STDCXX-294
 *
 * http://issues.apache.org/jira/browse/STDCXX-294
 *
 * $Id: 23.vector.cons.stdcxx-294.cpp 650370 2008-04-22 03:40:33Z sebor $
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

#include <assert.h>
#include <vector>

int main()
{
    static const int a[] = { 1, 2, 3, 4, 5 };
    std::vector<int> v (a, a + sizeof a / sizeof *a);

    v.insert (v.begin () + 2, 2, -1);

    static const int b[] = { 1, 2, -1, -1, 3, 4, 5 };

    const int pass = v == std::vector<int>(b, b + sizeof b / sizeof *b);

    assert (pass);

    return 1 - pass;
}
