/* Header     :
   Signature  :
   Description:
      static_assert is a reserved keyword.

      Assertions are evaluated at compile time.

 */

int main() {

    constexpr int x = 0;
    constexpr int y = 1;

#if 0
    static_assert(x == y, "x != y"); // error: static assertion failed: x != y
#endif

}
