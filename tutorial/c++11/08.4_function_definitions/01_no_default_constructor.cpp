/* https://msdn.microsoft.com/en-us/library/dn457344.aspx

   Benefits of explicitly defaulted functions
   1) if any costructor is explicitly declared, then
   > no default constructor is automatically generated.
*/

#include <stdio.h>

class C {
    int m_ival;
public:
    /* disable the default ctor */
    explicit C(int ival) : m_ival(ival) { }

    /* add back the default ctor */
    C() = default;

    void show() { printf("ival=%d\n", m_ival); }
};


main()
{
    C c1(10);
    C c2;

    c1.show();
    c2.show();
}
/*debug:
  ival=10
  ival=4196688
*/
