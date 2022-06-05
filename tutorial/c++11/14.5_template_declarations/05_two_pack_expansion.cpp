/* N3337 page 319, 14.5.3 Variadic templates [temp.variadic]
   See README.txt for variadic template syntax.
   Sample code from https://en.cppreference.com/w/cpp/language/parameter_pack

   compile with:
       g++ -g -std=c++11 -o exe 05_two_pack_expansion.cpp


   If the names of two parameter packs appear in the same pattern, they are
   expanded simultaneously, and they must have the same length:
 */

template<typename...>
struct Tuple { };

template<typename T1, typename T2>
struct Pair { };

template<class... Args1>
struct zip
{
    template<class... Args2>
    struct with
    {
        typedef Tuple<Pair<Args1,Args2>...> type;
        // Pair<Args1, Args2>... is the pack expansion
        // Pair<Args1, Args2>    is the pattern
    };
};

typedef zip<short, int>::with<unsigned short, unsigned>::type T1;
// T1 is Tuple<Pair<short,unsigned short>, Pair<int, unsigned>>

#if 0
typedef zip<short>::with<unsigned short, unsigned>::type T2;
// error: pack expansion contains parameter packs of different length
#endif


int main() {
}
