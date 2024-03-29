// checking for cv qualifiers on type void

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

#ifdef _RWSTD_NO_NEW_CLASS_TEMPLATE_SYNTAX
#  define _RWSTD_SPECIALIZED_CLASS
#else
#  define _RWSTD_SPECIALIZED_CLASS template<>
#endif

template <class T>
struct S {};

_RWSTD_SPECIALIZED_CLASS
struct S<void> {};

_RWSTD_SPECIALIZED_CLASS
struct S<const void> {};

_RWSTD_SPECIALIZED_CLASS
struct S<volatile void> {};

_RWSTD_SPECIALIZED_CLASS
struct S<const volatile void> {};
