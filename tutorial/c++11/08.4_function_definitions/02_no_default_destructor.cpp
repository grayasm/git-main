/* https://msdn.microsoft.com/en-us/library/dn457344.aspx

   Benefits of explicitly defaulted functions
   2) if a virtual destructor is explicitly declared, then
   > no default destructor is automatically generated.
*/

#include <stdio.h>

class A { /* an object */
public:
    A()  { printf("%s\n", __FUNCTION__); }
    ~A() { printf("%s\n", __FUNCTION__); }
};


class B { /* the base class */
public:
    virtual ~B() { printf("%s\n", __FUNCTION__); }
};


class D : public B { /* the derived class */
public:
    ~D()=default;
    A ma;
};


main()
{
    D d;
}

/*
  A
  ~A
  ~B
*/
