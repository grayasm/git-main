// checking for class std::bad_typeid

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

#ifndef _RWSTD_NO_TYPEINFO
#  include <typeinfo>
#else
#  ifndef _RWSTD_NO_TYPEINFO_H
#    include <typeinfo.h>
#  else

// 5.2.8, p6 [expr.typeid]:
// If the header <typeinfo> is not included prior to a use of typeid,
// the program is ill-formed.
namespace std {

class type_info { };

class bad_typeid { };

}   // namespace std

#  endif   // _RWSTD_NO_TYPEINFO_H
#endif   // _RWSTD_NO_TYPEINFO


#if 2 == __GNUG__
#  ifndef _RWSTD_NO_HONOR_STD
#    ifdef _RWSTD_NO_STD_TERMINATE
#      include "terminate.h"
#    endif   // _RWSTD_NO_STD_TERMINATE
#  endif   // _RWSTD_NO_HONOR_STD
#endif   // gcc 2.x


// force a failure if namespace std isn't honored
enum bad_typeid { };


struct S { virtual ~S () { } };

int main ()
{
    try {
        S *s = 0;

        // throws [std::] bad_typeid
        typeid (*s);
    }
    catch (std::bad_typeid&) {
        return 0;
    }
    catch (...) {
        // fail if typeid throws anything other than a std::bad_typeid
        return 1;
    }

    // fail if typeid doesn't throw
    return 2;
}
