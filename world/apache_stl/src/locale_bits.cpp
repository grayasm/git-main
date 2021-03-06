/***************************************************************************
 *
 * locale_bits.cpp - definitions of std::locale constant data members
 *
 * $Id: locale_bits.cpp 554089 2007-07-06 23:32:28Z sebor $
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
 * Copyright 1994-2006 Rogue Wave Software.
 * 
 **************************************************************************/

#define _RWSTD_LIB_SRC

#include <rw/_defs.h>

#include <loc/_locale.h>


_RWSTD_NAMESPACE (std) { 


_RWSTD_DEFINE_STATIC_CONST (const locale::category locale::none);
_RWSTD_DEFINE_STATIC_CONST (const locale::category locale::collate);
_RWSTD_DEFINE_STATIC_CONST (const locale::category locale::ctype);
_RWSTD_DEFINE_STATIC_CONST (const locale::category locale::monetary);
_RWSTD_DEFINE_STATIC_CONST (const locale::category locale::numeric);
_RWSTD_DEFINE_STATIC_CONST (const locale::category locale::time);
_RWSTD_DEFINE_STATIC_CONST (const locale::category locale::messages);
_RWSTD_DEFINE_STATIC_CONST (const locale::category locale::all);


}   // namespace std
