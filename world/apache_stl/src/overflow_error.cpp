/***************************************************************************
 *
 * overflow_error.cpp - definitions of class overflow_error members
 *
 * $Id: overflow_error.cpp 808358 2009-08-27 10:37:51Z faridz $
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

#define _RWSTD_LIB_SRC

#include <stdexcept>
#include <rw/_defs.h>


_RWSTD_NAMESPACE (std) {

// outlined to avoid generating a vtable in each translation unit
// that uses the class
/* virtual */ overflow_error::
~overflow_error () _THROWS (())
{
    // no-op
}

}   // namespace std
