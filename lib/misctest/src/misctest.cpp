/*
Copyright (C) 2012 Mihai Vasilian
*/

//acutest
#include "acutest.c"

//tests
#include "test_tree.hpp"

void run_test_tree()
{
    test_tree test;
    test.run();
}

TEST_LIST = {
    { "test_tree.hpp", run_test_tree },
    { NULL, NULL }
};
