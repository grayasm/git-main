/**************************************************************************
 *
 * isalnum.cpp - Example program of isalnum convience function.
 *
 * $Id: isalnum.cpp 550079 2007-06-23 18:34:25Z sebor $
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
 
#include <iostream>   // for cout, endl
#include <locale>     // for isalnum

#include <examples.h>

int main ()
{
    std::cout << "Alphanumeric ASCII characters: ";

    // iterate
    for (char c = '\0'; c != '\177'; ++c)
        if ((std::isalnum)(c, std::cout.getloc ()))
            std::cout << c << ' ';

    std::cout << std::endl;

    return 0;
}
