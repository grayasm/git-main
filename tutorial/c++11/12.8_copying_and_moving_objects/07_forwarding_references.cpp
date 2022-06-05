/*
  Forwarding references

  https://github.com/AnthonyCalandra/modern-cpp-features#forwarding-references

  A forwarding reference is created with the syntax T&& or auto&&

  lvalues stay as lvalues, temporaries are forwarded as rvalues.
  Forwarding references allow a reference to bind to either an lvalue or rvalue
  depending on the type.

  Forwarding references follow the rules of reference collapsing:

  T& &     becomes T&
  T& &&    becomes T&
  T&& &    becomes T&
  T&& &&   becomes T&&
 */

template<typename T>
void f (T&& t) {
}


int main()
{
    int x = 0;
    f (0);
    f (x);

    int& y = x;
    f (y);

    int&& z = 0;
    f (z);
    f (std::move(z));
}
