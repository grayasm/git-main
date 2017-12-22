/* Header     : none (core functionality)
   Signature  : auto 'variable initializer'
                auto function -> return type
   Description:

   ISO: The auto type-specifier signifies that the type of a variable
        being declared shall be deduced from its initializer
        or that a function declarator shall include a trailing-return-type.

   See: http://www.learncpp.com/cpp-tutorial/4-8-the-auto-keyword/
*/

int add(int x, int y);
// int show(auto x);  -- cannot infer x type at compile time

int main()
{
    auto d = 5.0;            // double
    auto i = 1 + 2;          // int
    auto sum = add(5, 6);    // int

    // from N3337 page 149
    auto x = 5;               // OK: x has type int
    const auto *v = &x, u = 6;// OK: v has type const int*, u has type const int
    static auto y = 0.0;      // OK: y has type double
    //auto int r;             // error: auto is not a storage-class-specifier

    return 0;
}


int add(int x, int y) { return x + y; }
/* int show(auto x)
   { std::cout << x; }

   The auto keyword can’t be used with function parameters.
   This won’t work, because the compiler can’t infer type for
   function parameter x at compile time.
*/
