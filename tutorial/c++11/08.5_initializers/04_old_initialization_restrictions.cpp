/* Header     : (core)
   Signature  :
   Description:

   This tutorial was found at:
   http://www.informit.com/articles/article.aspx?p=1852519

   Initialization in C++03 is tricky, to say the least, with four different
   initialization notations and far too many arbitrary restrictions and loopholes
     - no way to initialize a member array
     - no convenient way to initialize containers
     - no way to initialize dynamically allocated POD types

   C++03 imposes arbitrary restrictions in some cases, such as the inability
   to initialize member arrays.
*/

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;


class C
{
    int x[100];
    C(); // no proper way to initialize x
};

char *buff = new char[1024];  // no proper way to initialize the elements of buff

main()
{
    // no easy way to initialize members of a STL container.
    std::vector<string> vs;
    vs.push_back("alpha");
    vs.push_back("beta");
    vs.push_back("gamma");

    printf("initialization of member arrays\n");
}
