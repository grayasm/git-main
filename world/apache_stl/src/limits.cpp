/***************************************************************************
 *
 * limits.cpp - Source for the Standard Library limits class
 *
 * $Id: limits.cpp 660776 2008-05-28 01:48:19Z vitek $
 *
 ***************************************************************************
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
 * Copyright 1994-2008 Rogue Wave Software, Inc.
 * 
 **************************************************************************/

#define _RWSTD_LIB_SRC

#include <rw/_defs.h>  
                       
// define generic template and specializations
// use the quoted form of the #include directive to fool Sun C++
// otherwise the compiler fails to #include the header twice,
// most likely because it makes assumptions about headers with
// (C++) standard names
#include "limits"

#if _MSC_VER != 1300   // working around an MSVC 7.0 bug (PR #26562)
#  undef _RWSTD_LIMITS_INCLUDED
#  define _RWSTD_DEFINE_EXPORTS

   // define static data members of specializations
   // again, use the quoted form of the #include directive
#  include "limits"
#endif   // MSVC != 7.0
