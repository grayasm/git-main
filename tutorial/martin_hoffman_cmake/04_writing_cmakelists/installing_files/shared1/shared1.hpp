#ifndef __shared1_hpp__
#define __shared1_hpp__


/*    header1.hpp should be installed by CMake.
      The reason for this include is to check if install did indeed copied
      this header into the right place.
*/
#include "header1.hpp"

#ifndef __header1_hpp__
#error "header1.hpp" is missing
#endif


/*    For not having an empty shared library. */
void get_random_name(std::string& name);


#endif // __shared1_hpp__
