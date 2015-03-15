/***************************************************************************
 *
 * 24.operations.stdcxx-234 - regression test for STDCXX-234
 *   http://issues.apache.org/jira/browse/STDCXX-234
 *
 * $Id: 24.operations.stdcxx-234.cpp 671608 2008-06-25 17:24:43Z vitek $
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
 * Copyright 2007 Rogue Wave Software, Inc.
 *
 **************************************************************************/

#include <iterator>

struct X: std::iterator<std::random_access_iterator_tag, int> { };

namespace std {

// specialize the std::distance() function template of a user-defined
// iterator type to verify that the signature of the primary template
// is the same as the one of the specialization
template <> std::iterator_traits<X>::difference_type
distance<X> (X, X) { return 0; }

} // namespace std

int main ()
{
    return int (std::distance (X (), X ()));
}
