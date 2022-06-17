/* https://github.com/AnthonyCalandra/modern-cpp-features#raw-string-literals

   C++11 introduces a new way to declare string literals as
   "raw string literals". Character issued from an escape sequence (tabs,
   line feeds, single backslashes, etc) can be inputted raw while preserving
   formatting. This is useful, for example to write literary text, which
   might contain a lot of quotes or special formatting.

   A raw string literal is declared using the following syntax:

   R"delimiter(raw_characters)delimiter"

   * delimiter is an optional sequence of characters made of any source
     character except parantheses, backslashes and spaces.

   * raw_characters is any raw character sequence; must not contain the closing
     sequence ")delimiter".
*/

const char* msg1 = "\nHello,\n\tworld!\n";
const char* msg2 = R"(
Hello,
    world!
)";


int main(){
}
