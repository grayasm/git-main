/**************************************************************************
 *
 * stack.cpp - Example program of stack. See Class Reference Section
 *
 * $Id: stack.cpp 550079 2007-06-23 18:34:25Z sebor $
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

#include <stack>
#include <vector>
#include <deque>
#include <string>
#include <iostream>

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  //
  // Make a stack using a vector container.
  //
  stack<int,vector<int,allocator<int> > > s;
  //
  // Push a couple of values on the stack.
  //
  s.push(1);
  s.push(2);
  cout << s.top() << endl;
  //
  // Now pop them off.
  //
  s.pop();
  cout << s.top() << endl;
  s.pop();
  //
  // Make a stack of strings using a deque.
  //
  stack<string,deque<string,allocator<string> > > ss;
  //
  // Push a bunch of strings on then pop them off.
  //
  int i;
  for (i = 0; i < 10; i++)
  {
    ss.push(string(i+1,'a'));
    cout << ss.top() << endl;
  }
  for (i = 0; i < 10; i++)
  {
    cout << ss.top() << endl;
    ss.pop();
  }

  return 0;
}
