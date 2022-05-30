.
    C++11 N3337.pdf pag. 149
    7.2 Enumeration declarations

    An enum class is a strongly typed, strongly scoped enumeration.
    It does not convert implicitly to integer without static_cast.
    Refer to an enumerator of enum class only using full scope name.

    enum class altitude { high='h', low='l' };

    altitude a;           // OK
    a = high;             // error: high not in scope
    a = altitude::low;    // OK


    It can have a size, different than default int, using this syntax.
    enum class colors : char { red=1, green=2, blue=3 };
