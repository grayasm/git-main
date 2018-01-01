.
    C++11 N3337.pdf pag. 149
    7.2 Enumeration declarations

    enum class altitude { high='h', low='l' };

    altitude a;           // OK
    a = high;             // error: high not in scope
    a = altitude::low;    // OK


    enum class colors : char { red=1, green=2, blue=3 }; // set enum size
