.
    New C++11 Initialization Forms

    http://www.informit.com/articles/article.aspx?p=1852519
    this article explains very well the new c++11 initialization forms


    C++03 initialization old form:
    a) equal (=) sign:  int n = 0;  int m(0);
    b) constructor initialization list:  C::C(int x) : m_x(x) {}
    c) initialization of aggregates:  struct S{ int a,b; }; S s = {-3, -5};


    C++11 initialization uses { } brace-init form without the equal (=) sign:
    a) POD array:  vector<int> vi { 0,1,2,3 };
    b) class member initializers (=) or {...} do work at declaration time
    c) initializer lists or sequence contructors require a constructor and/or
       assignament operator with std::initializer_list as parameter


    The compiler does a lot of work behind { } brace-init as follows:
    - the default { } initializes with '\0', 0 or nullptr
    - char *p=new char[3] {'a','b','c'}; copies the val. directly into the array
    - std::initializer_list : the compiler can call the private ctor of this
      class passing a pointer (*) and a size_t length of a temporary array
      the compiler created from the values within the {...} brace-init

    C++11 examples:
    int a{0};
    string s{"hello"};
    string s2 { s };
    vector<int> vi { 0,1,2,3 };
    map<string, int> mm {{"one",1},{"two",2}};
    int *p{};  // nullptr
    double d{};// 0.0

    class C {
        int y[3] {0,1,2};
        double d=0;
        char *p {nullptr};
        C(std::initializer_list<int> il) {...} // implement code to loop il.
    };
