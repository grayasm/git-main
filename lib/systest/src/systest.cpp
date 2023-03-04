/*
Copyright (C) 2012 Mihai Vasilian
*/


// Testing framework
#include "acutest.c"



#include "test_critical_section.hpp"
#include "test_autocritical_section.hpp"
#include "test_event.hpp"
#include "test_filename.hpp"
#include "test_multi_lock.hpp"
#include "test_mutex.hpp"
#include "test_semaphore.hpp"
#include "test_single_lock.hpp"
#include "test_thread.hpp"
#include "test_time.hpp"


void run_test_autocritical_section()
{
    test_autocritical_section test;
    test.run();
}

void run_test_critical_section()
{
    test_critical_section test;
    test.run();
}

void run_test_event()
{
    test_event test;
    test.run();
}

void run_test_filename()
{
    test_filename test;
    test.run();
}

void run_test_multi_lock()
{
    test_multi_lock test;
    test.run();
}

void run_test_mutex()
{
    test_mutex test;
    test.run();
}

void run_test_semaphore()
{
    test_semaphore test;
    test.run();
}

void run_test_single_lock()
{
    test_single_lock test;
    test.run();
}

void run_test_thread()
{
    test_thread test;
    test.run_(); // collision with it's run()
}

void run_test_time()
{
    test_time test;
    test.run();
}

TEST_LIST = {
    { "test_critical_section.hpp", run_test_critical_section },
    { "test_autocritical_section.hpp", run_test_autocritical_section },
    { "test_event.hpp", run_test_event },
    { "test_filename.hpp", run_test_filename },
    { "test_multi_lock.hpp", run_test_multi_lock },
    { "test_mutex.hpp", run_test_mutex },
    { "test_semaphore.hpp", run_test_semaphore },
    { "test_single_lock.hpp", run_test_single_lock },
    { "test_thread.hpp", run_test_thread },
    { "test_time.hpp", run_test_time },
    { NULL, NULL }
};
