/*
   2.12 Keywords    [lex.key]
   N3337 page 22

   7.3.3 The using declaration  [namespace.udecl]

   A using-declaration introduces a name into the declarative region in which
   the using-declaration appears.
      using-declaration:
          using typename opt nested-name-specifier unqualified-id ;
          using :: unqualified-id ;

   https://github.com/AnthonyCalandra/modern-cpp-features#type-aliases

   Semantically similar to using a typedef however, type aliases with using
   are easier to read and are compatible with templates.
 */

#include <vector>
#include <string>


template<typename T>
using Vec = std::vector<T>;
using String = std::string;


int main(){

    Vec<int> v;
    String s { "foo" };
}
