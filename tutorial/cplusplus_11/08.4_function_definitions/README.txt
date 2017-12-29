.
    Defaulted and Deleted Functions - 11.03.2007 by Lawrence Crowl
    http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2210.html

    By default, C++ provides 4 default special member functions:
      destructor
      default constructor
      copy constructor
      copy assignment operator =

    By default, C++ applies several global operators to classes:
      sequence operator ,
      address-of operator &
      indirection operator *
      member access operator ->
      member indirection operator ->*
      free-store allocation operator new
      free-store deallocation operator delete

    The management of defaults has several problems:
      - declaring any constructor suppresses the default contructor
      - the default destructor is inappropriate to polymorphic classes
        requiring an explicit definition
      - once a default is suppressed, there is no means to resurrect it
      - default implementations are often more efficient than manually specified
        implementations
      - non-default implementations are non-trivial, which affects type
        semantics, e.g. makes a type non-POD
      - there is no means to prohibit a special member function or global
        operator without declaring a (non-trivial) substitute

    The C++11 proposed solution uses "=default;" and "=delete;" and
      - provides full control of special member function defaults
      - special member function definition are trivial at maximum
      - does not require modification of a class syntax
      - does NOT introduce new keywords
      - does not apply syntactically to data
      - applies to free functions as well as member functions

    Examples:

    class foobar {
    public:
        explicit foobar(int); // forces comp. not to generate the default ctor
    protected:
        foobar() = default;   // unless it is explicit told to do so;
                              // the compiler generated default is always public
    public:
        foobar(const foobar&) = delete;               // disabled
        foobar& operator=(const foobar&) = delete;    // disabled

        foobar(const object&&) = delete;  // avoid invoking the constructor with
                                          // a temporary
    };

    void write(double);
    void write(int) = delete;   // avoid invoking write(..) with an int argument

    template<typename T>
    void write(T value) = delete; // or even more restrictive here
                                  // avoid invoking write(..) with all other
                                  // arguments types
