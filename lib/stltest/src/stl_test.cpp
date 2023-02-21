/*
Copyright (C) 2012 Mihai Vasilian
*/


// Testing framework
#include "acutest.c"

// STL Tests
#include "test_algorithm.hpp"
#include "test_autoptr.hpp"
#include "test_basic_string.hpp"
#include "test_deque.hpp"
#include "test_exception.hpp"
#include "test_functional.hpp"
#include "test_list.hpp"
#include "test_numeric.hpp"
#include "test_priority_queue.hpp"
#include "test_queue.hpp"
#include "test_stack.hpp"
#include "test_utility.hpp"
#include "test_vector.hpp"


void run_test_algorithm()
{
    test_algorithm test;
    test.run();
}

void run_test_autoptr()
{
    test_autoptr test;
    test.run();
}

void run_test_basic_string() 
{
    test_basic_string test;
    test.run();
}

void run_test_deque()
{
    test_deque test;
    test.run();
}

void run_test_exception()
{
    test_exception test;
    test.run();
}

void run_test_functional()
{
    test_functional test;
    test.run();
}

void run_test_list()
{
    test_list test;
    test.run();
}

void run_test_numeric()
{
    test_numeric test;
    test.run();
}

void run_test_priority_queue() 
{
    test_priority_queue test;
    test.run();
}

void run_test_queue()
{
    test_queue test;
    test.run();
}

void run_test_stack()
{
    test_stack test;
    test.run();
}

void run_test_utility() 
{
    test_utility test;
    test.run();
}

void run_test_vector()
{
    test_vector test;
    test.run();
}

TEST_LIST = {
    { "test_algorithm.hpp", run_test_algorithm },
    { "test_autoptr.hpp", run_test_autoptr },
    { "test_basic_string.hpp", run_test_basic_string },
    { "test_deque.hpp", run_test_deque },
    { "test_exception.hpp", run_test_exception },
    { "test_functional.hpp", run_test_functional },
    { "test_list.hpp", run_test_list },
    { "test_numeric.hpp", run_test_numeric },
    { "test_priority_queue.hpp", run_test_priority_queue },
    { "test_queue.hpp", run_test_queue },
    { "test_stack.hpp", run_test_stack },
    { "test_utility.hpp", run_test_utility },
    { "test_vector.hpp", run_test_vector },
    { NULL, NULL }
};
