    N3337 page 273
    13.1  Overloadable declarations  [over.load]

    Member function declarations with the same name and the same
    parameter-type-list as well as member function template declarations
    with the same name, the same parameter-type-list, and the same
    template parameter lists cannot be overloaded if any of them, but not all,
    have a ref-qualifier.

    [ Example:
    class Y {
        void h() &;
        void h() const &;     // OK
        void h() &&;          // OK, all declarations have a ref-qualifier
        void i() &;
        void i() const;       // ill-formed, prior declaration of i
                              // has a ref-qualifier
    };
    -- end example]
