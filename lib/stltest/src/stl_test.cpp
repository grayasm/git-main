/*
Copyright (C) 2012 Mihai Vasilian
*/



//cppunit
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


#include "test_algorithm.hpp"
#include "test_autoptr.hpp"
#include "test_deque.hpp"
#include "test_exception.hpp"
#include "test_functional.hpp"
#include "test_generic_array.hpp"
#include "test_list.hpp"
#include "test_numeric.hpp"
#include "test_generic_string.hpp"
#include "test_vector.hpp"
#include "test_priority_queue.hpp"
#include "test_queue.hpp"
#include "test_stack.hpp"
#include "test_utility.hpp"
#include "test_basic_string.hpp"
#include "test_vector.hpp"
#include "test_list.hpp"



int main(int argc, char** argv)
{
	// disable stdout buffer
	setvbuf(stdout, NULL, _IONBF, 0);

    //http://cppunit.sourceforge.net/doc/lastest/cppunit_cookbook.html

#if 1
    CPPUNIT_TEST_SUITE_REGISTRATION(test_algorithm);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_autoptr);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_basic_string);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_deque);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_exception);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_functional);

    CPPUNIT_TEST_SUITE_REGISTRATION(test_numeric);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_utility);
#endif



    
    CPPUNIT_TEST_SUITE_REGISTRATION(test_vector);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_list);


    //////////////////////////////////////////////////////////////////////////
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( registry.makeTest() );
    //runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    bool wasSucessful = runner.run();
    return wasSucessful ? 0:1;
}  // main
