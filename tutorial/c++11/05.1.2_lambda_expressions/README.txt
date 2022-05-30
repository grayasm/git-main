.
   Here is a complete (I hope) description of the lambda function.
   It is implemented as an operator[1] (global, or local to a class/structure).
   It takes a number of arguments.
   It returns a value.
   Can be const or mutable.
   Can throw and exception or not.
   Can have attributes like implementation-defined language extensions,
       i.e. GNU extension __attribute__((...)), or Microsoft __declspec(), etc.
   For more details see: http://en.cppreference.com/w/cpp/language/attributes
   For samples see [2]

   -----------------------------------------------------------------------------

   Header     : core feature
   Signature  : [ captures ] (params) specifiers exception attr -> ret { body };
                [ captures ] (params) -> ret { body };
                [ captures ] (params) { body };
                [ captures ] { body };

   Description:
       captures  : [] nothing
                   [=] all by copy and *this by reference (if any)
                   [&] all by reference and *this by reference (if any)
                   [this] *this by reference
                   [a, &b] a by copy, b by reference
       specifiers: mutable   - can modify all captures by copy[=] and call their
                               non-const member functions
                   constexpr - default, obey constexpr functions
       exception : throw
                   noexcept
       attr      : [[attr]] [[attr1, attr2(args)]] [[namespace::attr(args)]] alignas_specifier
                   ex: [[noreturn]] void f() { throw "error" ; }
                   [[carries_dependency]]
                   [[deprecated]], [[deprecated("reason")]]
                   [[fallthrough]]
                   [[nodiscard]]
                   [[maybe_unused]], etc...
       ret       : default void or explicit, e.g. auto&, int&, char*, SomeClass
       body      : function body
   -----------------------------------------------------------------------------

   [1]
   ret operator() (params) const { body }   // mutable keyword not used
   ret operator() (params) { body }         // mutable keyword

   template<template-params>                // generic lambda (c++14, anyway)
   ret operator() (params) { body }         // template not in the examples

   -----------------------------------------------------------------------------
   [2]
   // lambda requires ; termination. Here is omitted for simplicity.

   []() { }                           // ok, empty lambda
   []() { return 10; }                // ok
   []() { return x; }                 // error: x is not captured
   []() { return this->val; }         // error: this was not captured for this lambda function

   [=]() { return x*2; }              // ok, capture all by copy, x read-only
   [=]() { x = 2; }                   // error: assignament of read-only variable x
   [=]() mutable { x = 2; }           // ok, x is 2 only inside lambda
   [=]() { this->val = 2; }           // ok, val modified also outside lambda
   [=]() { return this->val; }        // ok, capture this by reference

   [&]() { x = 2; }                   // ok, x is 2 also outside lambda
   [&]() { this->val = 2; }           // ok, val modified also outside lambda
   [&]() { return this->val; }        // ok, capture this by reference

   [](int x) { x = 2; }               // ok, no capture, arg x is 2 inside only
   [](int& x) { x = 2; }              // ok, no capture, passed arg gets modified outside too
   [](int* x) { *x = 2; }             // ok, pointer gets modified outside too

   // lambda is a function that must be invoked explictly - not called by default
   void (*f)() = []() { };
   f();

   // inside a method void g() of class A the signature of lambda get complicated:
   A::get::__lambda0    and I could not declare a function f of this type.
   Instead I had to use either auto f, or std::function

   auto f = [=](int mul) -> float { return this->fval * mul; };    or,

   #include <functional>
   std::function<float(int)> f = [=](int mul) -> float { return this->fval*mul;};
   -----------------------------------------------------------------------------
