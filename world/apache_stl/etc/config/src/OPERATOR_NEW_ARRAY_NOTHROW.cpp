// checking for operator new[] (size_t, nothrow_t)

/***************************************************************************
 *
 * Licensed to the Apache Software  Foundation (ASF) under one or more
 * contributor  license agreements.  See  the NOTICE  file distributed
 * with  this  work  for  additional information  regarding  copyright
 * ownership.   The ASF  licenses this  file to  you under  the Apache
 * License, Version  2.0 (the  License); you may  not use  this file
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
 * Copyright 1999-2007 Rogue Wave Software, Inc.
 * 
 **************************************************************************/

#include "config.h"

#include <stddef.h>


#ifndef _RWSTD_NO_NAMESPACE
# ifndef _RWSTD_NO_STD_NOTHROW_T   

namespace std {

# endif // _RWSTD_NO_STD_NOTHROW_T
#endif // _RWSTD_NO_NAMESPACE
    
struct nothrow_t { };

#ifndef _RWSTD_NO_NAMESPACE
# ifndef _RWSTD_NO_STD_NOTHROW_T   

}  // end namespace std

using std::nothrow_t;

# endif // _RWSTD_NO_STD_NOTHROW_T
#endif // _RWSTD_NO_NAMESPACE

#ifdef _RWSTD_NO_EXCEPTION_SPECIFICATION
#  define throw()
#endif   // _RWSTD_NO_EXCEPTION_SPECIFICATION

void* operator new[] (size_t, const nothrow_t&) throw ();

int main ()
{
    ::operator new[] (1, nothrow_t ());
    return 0;
}
