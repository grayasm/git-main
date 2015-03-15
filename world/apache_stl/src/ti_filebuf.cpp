/***************************************************************************
 *
 * ti_filebuf.cpp - explicit instantiation directives
 *                  for basic_filebuf<char>
 *
 * $Id: ti_filebuf.cpp 671102 2008-06-24 09:37:33Z faridz $
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
 * Copyright 1994-2006 Rogue Wave Software.
 * 
 **************************************************************************/

#define _RWSTD_LIB_SRC

#define _RWSTD_INSTANTIATE_TEMPLATES       1
#define _RWSTD_INSTANTIATE_BASIC_FILEBUF   1
#define _RWSTD_INSTANTIATE_CHAR            1

#include <rw/_defs.h>

#undef _RWSTD_NO_TEMPLATE_DEFINITIONS

#ifdef _RWSTD_MSVC
   // shut up the bogus MSVC warning C4661: no suitable definition
   // provided for explicit template instantiation request
#  pragma warning (disable: 4661)
#endif   // _RWSTD_MSVC

// include <cstdio> to define the extended member functions that
// take a FILE* argument
#include <cstdio>
#include <fstream>
