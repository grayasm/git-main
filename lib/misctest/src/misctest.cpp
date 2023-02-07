/*
Copyright (C) 2012 Mihai Vasilian
*/



//cppunit
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "test_tree.hpp"


int main(int argc, char** argv)
{
	// disable stdout buffer
	setvbuf(stdout, NULL, _IONBF, 0);
	
    //http://cppunit.sourceforge.net/doc/lastest/cppunit_cookbook.html

	
#if 1
//    CPPUNIT_TEST_SUITE_REGISTRATION(test_tree); -- exception test_tree::preorder_it (E)
#endif


    //////////////////////////////////////////////////////////////////////////
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest( registry.makeTest() );
    //runner.setOutputter( new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    bool wasSucessful = runner.run();
    return wasSucessful ? 0:1;
}  // main
