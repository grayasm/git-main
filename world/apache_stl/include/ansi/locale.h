/***************************************************************************
 *
 * locale.h
 *
 * $Id: locale.h 550089 2007-06-23 19:18:07Z sebor $
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

#include <rw/_defs.h>

#ifndef _RWSTD_NO_DEPRECATED_C_HEADERS
#  ifndef _RWSTD_LOCALE_H_INCLUDED
#    define _RWSTD_LOCALE_H_INCLUDED

#    include <clocale>

#    ifndef _RWSTD_NO_NAMESPACE

using std::lconv;

using std::localeconv;
using std::setlocale;
#    endif   // _RWSTD_NO_NAMESPACE
#  endif   // _RWSTD_LOCALE_H_INCLUDED
#else
#  include _RWSTD_ANSI_C_LOCALE_H
#endif   // _RWSTD_NO_DEPRECATED_C_HEADERS
