.
    C++ Rvalue References Explained by Thomas Becker
    http://thbecker.net/articles/rvalue_references/section_01.html

    C++11 N3337.pdf
    12.8 Copying and moving class objects pag.261

    The topic cannot be learned from ISO. The T.Becker tutorial is excelent.
    A short summary:
    ---------------

    int a = 32;  // an lvalue
    int b = 33;
    a * b = 34;  // error, a*b is a temporary rvalue

    int bar();
    bar() = 35;  // error, bar() returns an rvalue

    void foo(X&);
    void foo(X&&);
    X x;
    X bar();
    foo(x);      // calls foo(X&) , argument is lvalue
    foo(bar());  // calls foo(X&&), argument is rvalue

    void foo(X&& x)
    {
        X anotherX = x; /* If it has a name, then it is an lvalue.
                           This will call X(const X& tc)
                           x can be accessed after assignment, so it's not
                           a temporary, therefore it will not be moved.
                           Remember moved objects are left in undefined state.
                        */
    }

    /* move constructor */
    X(X&& tm)
    {
        ptr = tm.ptr;
        len = tm.len;
        tm.ptr = nullptr;
        tm.len = 0;
    }

    /* move assignment operator */
    X& operator=(X&& tm)
    {
        if(this != &tm)
        {
            if(ptr != nullptr) delete [] ptr;
            ptr = tm.ptr;
            len = tm.len;
            tm.ptr = nullptr;
            tm.len = 0;
        }
        return *this;
    }

    C++11 defines new collapsing rules:
    A& &  becomes A&
    A& && becomes A&
    A&& & becomes A&
    A&& && becomes A&&

    , and these are used by std::forward and std::move implementations.

    Using of std::move and std::forward:
    X x(100);
    X y = std::move(x); // x left in undefined state

    X&& foo()
    {
        X x(100);
        return std::forward<X>(x); // similar with static_cast<X&&>(x);
    }
