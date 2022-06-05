/*
  see README.txt

  https://github.com/AnthonyCalandra/modern-cpp-features#explicit-conversion-functions

  Conversion functions can now be made explicit using the 'explicit' specifier.
 */


struct A {
    operator bool() const { return true; }
};

struct B {
    explicit operator bool() const { return true; }
};


int main(){

    A a;
    if (a) { }      // OK calls A::operator bool()
    bool ba = a;    // OK copy-initialization selects  A::operator bool()


    B b;
    if (b) { }     // OK calls B::operator bool()

#if 0
    bool bb = b;   // error copy-initialization does not consider B::operator bool()
#endif


}
