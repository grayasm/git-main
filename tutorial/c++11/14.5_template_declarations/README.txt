14.5.3 Variadic templates      [temp.variadic]

1. A template parameter pack is a template parameter that accepts
   zero or more template arguments.

   template<class ... Types> struct Tuple { };

   Tuple<> t0;                  // Types contains no arguments
   Tuple<int> t1;               // Types contains one argument: int
   Tuple<int, float> t2;        // Types contains two arguments: int and float
   Tuple<0> error;              // error: 0 is not a type

2. A function parameter pack is a function parameter that accepts
   zero or more function arguments.

   template<class ... Types> void f(Types ... args);

   f();                         // OK: args contains no arguments
   f(1);                        // OK: args contains one arguement: int
   f(2, 1.0);                   // OK: args contains two arguments: int and double

3. A parameter pack is either a template parameter pack
   or a function parameter pack.

4. A pack expansion consists of a pattern and an ellipsis, the instantiation
   of which produces zero or more instantiations of the pattern in a list.

   template<class ... Types> void f(Types ... rest);

   template<class ... Types> void g(Types ... rest) {
       f(&rest ...); // “&rest ...” is a pack expansion; “&rest” is its pattern
   }

5. A parameter pack whose name appears within the pattern of a pack expansion
   is expanded by that pack expansion.

   template<typename...> struct Tuple {};
   template<typename T1, typename T2> struct Pair {};

   template<class ... Args1> struct zip {
       template<class ... Args2> struct with {
           typedef Tuple<Pair<Args1, Args2> ... > type;
       };
   };

   typedef zip<short, int>::with<unsigned short, unsigned>::type T1;
       // T1 is Tuple<Pair<short, unsigned short>, Pair<int, unsigned>>

   typedef zip<short>::with<unsigned short, unsigned>::type T2;
       // error: different number of arguments specified for Args1 and Args2

   template<class ... Args>
   void g(Args ... args) {
       // OK: Args is expanded by the function parameter pack args
       f(const_cast<const Args*>(&args)...); // OK: “Args” and “args” are expanded
       f(5 ...);                             // error: pattern does not contain any parameter packs
       f(args);                              // error: parameter pack "args" is not expanded
       f(h(args ...) + args ...);            // OK: first "args" expanded with h, second "args" expanded withing f.
   }

6. The instantiation of a pack expansion that is not a sizeof... expression
   produces a list E 1 , E 2 , ..., E N , where N is the number of elements
   in the pack expansion parameters.

   template<class... T> struct X : T... { };
   template<class... T> void f(T... values) {
       X<T...> x(values...);
   }

   template void f<>(); // OK: X<> has not base classes
                        // x is a variable of type X<> that is value initialized
