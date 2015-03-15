// implementation file for instantiation_before_definition.h

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

template <class T>
T instantiated_before_defined (T t)
{
    return t;
}

template <class T>
T
InstantiatedBeforeDefined<T>::
instantiated_first (T t)
{
    return instantiated_before_defined (t);
}

template <class T>
T
InstantiatedBeforeDefined<T>::
instantiated_first_and_referenced (T t) const
{
    return instantiated_before_defined (t);
}
