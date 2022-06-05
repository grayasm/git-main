/*
  N3337 page 167
  7.6 Attributes  [dcl.attr]
  7.6.3 Noreturn attribute

  https://github.com/AnthonyCalandra/modern-cpp-features#attributes

  Attributes
  Attributes provide a universal syntax over __attribute__(...),__declspec,etc
 */


// 'noreturn' attribute indicates 'f' doesn't return.
[[ noreturn ]] void f() {
    throw "error";
}


int main(){

    f();

}
