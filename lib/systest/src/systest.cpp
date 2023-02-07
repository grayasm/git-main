/*
Copyright (C) 2012 Mihai Vasilian
*/



//cppunit
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


#include "test_critical_section.hpp"
#include "test_autocritical_section.hpp"
#include "test_event.hpp"
#include "test_multi_lock.hpp"
#include "test_mutex.hpp"
#include "test_semaphore.hpp"
#include "test_single_lock.hpp"
#include "test_thread.hpp"
#include "test_time.hpp"


int main(int argc, char** argv)
{
	// disable stdout buffer
	setvbuf(stdout, NULL, _IONBF, 0);
	
    //http://cppunit.sourceforge.net/doc/lastest/cppunit_cookbook.html


#if 1
    CPPUNIT_TEST_SUITE_REGISTRATION(test_critical_section);
	CPPUNIT_TEST_SUITE_REGISTRATION(test_autocritical_section);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_mutex);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_semaphore);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_event);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_multi_lock);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_single_lock);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_thread);
    CPPUNIT_TEST_SUITE_REGISTRATION(test_time);
#endif
	

    //////////////////////////////////////////////////////////////////////////
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( registry.makeTest() );
    //runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    bool wasSucessful = runner.run();
    return wasSucessful ? 0:1;
}  // main
