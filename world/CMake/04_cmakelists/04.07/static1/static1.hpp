#ifndef __static1_hpp__
#define __static1_hpp__

/*    header1.hpp should be installed by CMake.
      The reason for this include is to check if install did indeed copied
      this header into the right place.
 */
#include "header1.hpp"


#ifndef __header1_hpp__
#error "header1.hpp" is missing
#endif


/*    For not having an empty static library. */
void get_random_color (int& r, int& g, int& b);



#endif // __static1_hpp__
