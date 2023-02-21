/*  <Mihai Vasilian> 2023-02-21
    Split acutest.h in 2 files
    acutest.h - header
    acutest.c - source
*/
/*
 * Acutest -- Another C/C++ Unit Test facility
 * <https://github.com/mity/acutest>
 *
 * Copyright 2013-2020 Martin Mitas
 * Copyright 2019 Garrett D'Amore
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef ACUTEST_H
#define ACUTEST_H


/************************
 *** Public interface ***
 ************************/

/* By default, "acutest.h" provides the main program entry point (function
 * main()). However, if the test suite is composed of multiple source files
 * which include "acutest.h", then this causes a problem of multiple main()
 * definitions. To avoid this problem, #define macro TEST_NO_MAIN in all
 * compilation units but one.
 */

/* Macro to specify list of unit tests in the suite.
 * The unit test implementation MUST provide list of unit tests it implements
 * with this macro:
 *
 *   TEST_LIST = {
 *       { "test1_name", test1_func_ptr },
 *       { "test2_name", test2_func_ptr },
 *       ...
 *       { NULL, NULL }     // zeroed record marking the end of the list
 *   };
 *
 * The list specifies names of each test (must be unique) and pointer to
 * a function implementing it. The function does not take any arguments
 * and has no return values, i.e. every test function has to be compatible
 * with this prototype:
 *
 *   void test_func(void);
 *
 * Note the list has to be ended with a zeroed record.
 */
#define TEST_LIST               const struct acutest_test_ acutest_list_[]


/* Macros for testing whether an unit test succeeds or fails. These macros
 * can be used arbitrarily in functions implementing the unit tests.
 *
 * If any condition fails throughout execution of a test, the test fails.
 *
 * TEST_CHECK takes only one argument (the condition), TEST_CHECK_ allows
 * also to specify an error message to print out if the condition fails.
 * (It expects printf-like format string and its parameters). The macros
 * return non-zero (condition passes) or 0 (condition fails).
 *
 * That can be useful when more conditions should be checked only if some
 * preceding condition passes, as illustrated in this code snippet:
 *
 *   SomeStruct* ptr = allocate_some_struct();
 *   if(TEST_CHECK(ptr != NULL)) {
 *       TEST_CHECK(ptr->member1 < 100);
 *       TEST_CHECK(ptr->member2 > 200);
 *   }
 */
#define TEST_CHECK_(cond,...)   acutest_check_((cond), __FILE__, __LINE__, __VA_ARGS__)
#define TEST_CHECK(cond)        acutest_check_((cond), __FILE__, __LINE__, "%s", #cond)


/* These macros are the same as TEST_CHECK_ and TEST_CHECK except that if the
 * condition fails, the currently executed unit test is immediately aborted.
 *
 * That is done either by calling abort() if the unit test is executed as a
 * child process; or via longjmp() if the unit test is executed within the
 * main Acutest process.
 *
 * As a side effect of such abortion, your unit tests may cause memory leaks,
 * unflushed file descriptors, and other phenomena caused by the abortion.
 *
 * Therefore you should not use these as a general replacement for TEST_CHECK.
 * Use it with some caution, especially if your test causes some other side
 * effects to the outside world (e.g. communicating with some server, inserting
 * into a database etc.).
 */
#define TEST_ASSERT_(cond,...)                                                 \
    do {                                                                       \
        if(!acutest_check_((cond), __FILE__, __LINE__, __VA_ARGS__))           \
            acutest_abort_();                                                  \
    } while(0)
#define TEST_ASSERT(cond)                                                      \
    do {                                                                       \
        if(!acutest_check_((cond), __FILE__, __LINE__, "%s", #cond))           \
            acutest_abort_();                                                  \
    } while(0)


#ifdef __cplusplus
/* Macros to verify that the code (the 1st argument) throws exception of given
 * type (the 2nd argument). (Note these macros are only available in C++.)
 *
 * TEST_EXCEPTION_ is like TEST_EXCEPTION but accepts custom printf-like
 * message.
 *
 * For example:
 *
 *   TEST_EXCEPTION(function_that_throw(), ExpectedExceptionType);
 *
 * If the function_that_throw() throws ExpectedExceptionType, the check passes.
 * If the function throws anything incompatible with ExpectedExceptionType
 * (or if it does not thrown an exception at all), the check fails.
 */
#define TEST_EXCEPTION(code, exctype)                                          \
    do {                                                                       \
        bool exc_ok_ = false;                                                  \
        const char *msg_ = NULL;                                               \
        try {                                                                  \
            code;                                                              \
            msg_ = "No exception thrown.";                                     \
        } catch(exctype const&) {                                              \
            exc_ok_= true;                                                     \
        } catch(...) {                                                         \
            msg_ = "Unexpected exception thrown.";                             \
        }                                                                      \
        acutest_check_(exc_ok_, __FILE__, __LINE__, #code " throws " #exctype);\
        if(msg_ != NULL)                                                       \
            acutest_message_("%s", msg_);                                      \
    } while(0)
#define TEST_EXCEPTION_(code, exctype, ...)                                    \
    do {                                                                       \
        bool exc_ok_ = false;                                                  \
        const char *msg_ = NULL;                                               \
        try {                                                                  \
            code;                                                              \
            msg_ = "No exception thrown.";                                     \
        } catch(exctype const&) {                                              \
            exc_ok_= true;                                                     \
        } catch(...) {                                                         \
            msg_ = "Unexpected exception thrown.";                             \
        }                                                                      \
        acutest_check_(exc_ok_, __FILE__, __LINE__, __VA_ARGS__);              \
        if(msg_ != NULL)                                                       \
            acutest_message_("%s", msg_);                                      \
    } while(0)
#endif  /* #ifdef __cplusplus */


/* Sometimes it is useful to split execution of more complex unit tests to some
 * smaller parts and associate those parts with some names.
 *
 * This is especially handy if the given unit test is implemented as a loop
 * over some vector of multiple testing inputs. Using these macros allow to use
 * sort of subtitle for each iteration of the loop (e.g. outputting the input
 * itself or a name associated to it), so that if any TEST_CHECK condition
 * fails in the loop, it can be easily seen which iteration triggers the
 * failure, without the need to manually output the iteration-specific data in
 * every single TEST_CHECK inside the loop body.
 *
 * TEST_CASE allows to specify only single string as the name of the case,
 * TEST_CASE_ provides all the power of printf-like string formatting.
 *
 * Note that the test cases cannot be nested. Starting a new test case ends
 * implicitly the previous one. To end the test case explicitly (e.g. to end
 * the last test case after exiting the loop), you may use TEST_CASE(NULL).
 */
#define TEST_CASE_(...)         acutest_case_(__VA_ARGS__)
#define TEST_CASE(name)         acutest_case_("%s", name)


/* Maximal output per TEST_CASE call. Longer messages are cut.
 * You may define another limit prior including "acutest.h"
 */
#ifndef TEST_CASE_MAXSIZE
    #define TEST_CASE_MAXSIZE    64
#endif


/* printf-like macro for outputting an extra information about a failure.
 *
 * Intended use is to output some computed output versus the expected value,
 * e.g. like this:
 *
 *   if(!TEST_CHECK(produced == expected)) {
 *       TEST_MSG("Expected: %d", expected);
 *       TEST_MSG("Produced: %d", produced);
 *   }
 *
 * Note the message is only written down if the most recent use of any checking
 * macro (like e.g. TEST_CHECK or TEST_EXCEPTION) in the current test failed.
 * This means the above is equivalent to just this:
 *
 *   TEST_CHECK(produced == expected);
 *   TEST_MSG("Expected: %d", expected);
 *   TEST_MSG("Produced: %d", produced);
 *
 * The macro can deal with multi-line output fairly well. It also automatically
 * adds a final new-line if there is none present.
 */
#define TEST_MSG(...)           acutest_message_(__VA_ARGS__)


/* Maximal output per TEST_MSG call. Longer messages are cut.
 * You may define another limit prior including "acutest.h"
 */
#ifndef TEST_MSG_MAXSIZE
    #define TEST_MSG_MAXSIZE    1024
#endif


/* Macro for dumping a block of memory.
 *
 * Its intended use is very similar to what TEST_MSG is for, but instead of
 * generating any printf-like message, this is for dumping raw block of a
 * memory in a hexadecimal form:
 *
 *   TEST_CHECK(size_produced == size_expected &&
 *              memcmp(addr_produced, addr_expected, size_produced) == 0);
 *   TEST_DUMP("Expected:", addr_expected, size_expected);
 *   TEST_DUMP("Produced:", addr_produced, size_produced);
 */
#define TEST_DUMP(title, addr, size)    acutest_dump_(title, addr, size)

/* Maximal output per TEST_DUMP call (in bytes to dump). Longer blocks are cut.
 * You may define another limit prior including "acutest.h"
 */
#ifndef TEST_DUMP_MAXSIZE
    #define TEST_DUMP_MAXSIZE   1024
#endif


/* Common test initialiation/clean-up
 *
 * In some test suites, it may be needed to perform some sort of the same
 * initialization and/or clean-up in all the tests.
 *
 * Such test suites may use macros TEST_INIT and/or TEST_FINI prior including
 * this header. The expansion of the macro is then used as a body of helper
 * function called just before executing every single (TEST_INIT) or just after
 * it ends (TEST_FINI).
 *
 * Examples of various ways how to use the macro TEST_INIT:
 *
 *   #define TEST_INIT      my_init_func();
 *   #define TEST_INIT      my_init_func()      // Works even without the semicolon
 *   #define TEST_INIT      setlocale(LC_ALL, NULL);
 *   #define TEST_INIT      { setlocale(LC_ALL, NULL); my_init_func(); }
 *
 * TEST_FINI is to be used in the same way.
 */

 /**********************
  *** Implementation ***
  **********************/

  /* The unit test files should not rely on anything below. */

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
#define ACUTEST_UNIX_       1
#include <errno.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#if defined CLOCK_PROCESS_CPUTIME_ID  &&  defined CLOCK_MONOTONIC
#define ACUTEST_HAS_POSIX_TIMER_    1
#endif
#endif

#if defined(_gnu_linux_) || defined(__linux__)
#define ACUTEST_LINUX_      1
#include <fcntl.h>
#include <sys/stat.h>
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#define ACUTEST_WIN_        1
#include <windows.h>
#include <io.h>
#endif

#if defined(__APPLE__)
#define ACUTEST_MACOS_
#include <assert.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sysctl.h>
#endif

#ifdef __cplusplus
#include <exception>
#endif

#ifdef __has_include
#if __has_include(<valgrind.h>)
#include <valgrind.h>
#endif
#endif

/* Enable the use of the non-standard keyword __attribute__ to silence warnings under some compilers */
#if defined(__GNUC__) || defined(__clang__)
#define ACUTEST_ATTRIBUTE_(attr)    __attribute__((attr))
#else
#define ACUTEST_ATTRIBUTE_(attr)
#endif


/* Note our global private identifiers end with '_' to mitigate risk of clash
 * with the unit tests implementation. */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
    /* In the multi-platform code like ours, we cannot use the non-standard
     * "safe" functions from Microsoft C lib like e.g. sprintf_s() instead of
     * standard sprintf(). Hence, lets disable the warning C4996. */
#pragma warning(push)
#pragma warning(disable: 4996)
#endif


    struct acutest_test_ {
        const char* name;
        void (*func)(void);
    };

    struct acutest_test_data_ {
        unsigned char flags;
        double duration;
    };

    enum {
        ACUTEST_FLAG_RUN_ = 1 << 0,
        ACUTEST_FLAG_SUCCESS_ = 1 << 1,
        ACUTEST_FLAG_FAILURE_ = 1 << 2,
    };

    extern const struct acutest_test_ acutest_list_[];

    int acutest_check_(int cond, const char* file, int line, const char* fmt, ...);
    void acutest_case_(const char* fmt, ...);
    void acutest_message_(const char* fmt, ...);
    void acutest_dump_(const char* title, const void* addr, size_t size);
    void acutest_abort_(void) ACUTEST_ATTRIBUTE_(noreturn);


#ifdef __cplusplus
    }  /* extern "C" */
#endif


#endif  /* #ifndef ACUTEST_H */
