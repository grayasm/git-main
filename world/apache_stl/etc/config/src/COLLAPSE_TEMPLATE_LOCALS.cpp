// checking static locals in template code

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

#if 0   // guard invalid preprocessor symbol below

   // establish a dependency on collapse_template_locals.lib.*
#  ifndef _RWSTD_NO_collapse_template_locals.lib

     // link this compiled translation unit with the lib below
     // LDOPTS = collapse_template_locals.lib$(LIBSUFFIX)

#  endif   // _RWSTD_NO_collapse_template_locals.lib
#endif   // 0


// also defined in collapse_template_locals.lib.cpp
template <class T>
T foo (T)
{
    // multiple instances of `t' must be collapsed
    static T t;
    return t++;
}

// bar() returns foo (0)
extern int bar ();


int main ()
{
    // compilers that corectly collapse static locals will
    // behave as commented below (others will return 0 from bar())

    int i = foo (0);   // returns 0
    int j = bar ();    // should return 1

    return !(i != j);
}
