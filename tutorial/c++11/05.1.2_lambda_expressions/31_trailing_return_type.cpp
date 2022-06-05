/* https://github.com/AnthonyCalandra/modern-cpp-features#ref-qualified-member-functions

   This feature is especially useful when certain return types cannot
   be resolved.
 */


// Note the use of 'auto' and 'decltype(..)'
template<typename T, typename U>
auto add(T a, U b) ->decltype(a + b) {
    return a + b;
}


int main(){
}
