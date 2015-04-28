/*
  Copyright (C) 2012 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
*/



//cppunit
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


#include "test_algorithm.hpp"
#include "test_autoptr.hpp"
#include "test_critical_section.hpp"
#include "test_deque.hpp"
#include "test_event.hpp"
#include "test_exception.hpp"
#include "test_filename.hpp"
#include "test_functional.hpp"
#include "test_generic_array.hpp"
#include "test_list.hpp"
#include "test_multi_lock.hpp"
#include "test_mutex.hpp"
#include "test_numeric.hpp"
#include "test_generic_string.hpp"
#include "test_vector.hpp"
#include "test_priority_queue.hpp"
#include "test_queue.hpp"
#include "test_semaphore.hpp"
#include "test_single_lock.hpp"
#include "test_stack.hpp"
#include "test_thread.hpp"
#include "test_tree.hpp"
#include "test_utility.hpp"
#include "test_vector.hpp"
#include "test_time.hpp"


int main(int argc, char** argv)
{
    //http://cppunit.sourceforge.net/doc/lastest/cppunit_cookbook.html

    //////////////////////////////////////////////////////////////////////////
    //algorithms
    /*
      algorithm
      functional
      math
      memmanip
      memory
      numeric
      utility
    */

#if 0
    CPPUNIT_TEST_SUITE_REGISTRATION(test_algorithm);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_functional);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_numeric);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_utility);
#endif


    //////////////////////////////////////////////////////////////////////////
    //containers
    /*
      autoptr
      exception
      iterator
      generic_array
      vector
      string
      list
      stack
      deque
      queue
      priority_queue
      tree
    */
	
#if 0
    CPPUNIT_TEST_SUITE_REGISTRATION(test_autoptr);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_exception);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_generic_array);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_vector);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_generic_string);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_list);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_stack);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_deque);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_queue);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_priority_queue);
//    CPPUNIT_TEST_SUITE_REGISTRATION(test_tree); -- exception test_tree::preorder_it (E)
#endif


    //////////////////////////////////////////////////////////////////////////
    //misc libraries
    /*
      stdio
      unistd
      strconv
      stream
      filename
      critical_section
      mutex
      semaphore
      event
      multi_lock
      single_lock
      thread
      time 
   */

#if 0
    CPPUNIT_TEST_SUITE_REGISTRATION(test_filename);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_critical_section);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_mutex);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_semaphore);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_event);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_multi_lock);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_single_lock);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_thread);
	CPPUNIT_TEST_SUITE_REGISTRATION(test_time);
#endif
	CPPUNIT_TEST_SUITE_REGISTRATION(test_thread);
	
	

    //////////////////////////////////////////////////////////////////////////
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( registry.makeTest() );
    //runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    bool wasSucessful = runner.run();
    return wasSucessful ? 0:1;
}  // main
