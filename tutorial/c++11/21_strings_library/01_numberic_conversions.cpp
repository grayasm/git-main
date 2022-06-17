/* N3337, page 639
   21.5 Numeric conversions


   int stoi(const string& str, size_t *idx = 0, int base = 10);
   long stol(const string& str, size_t *idx = 0, int base = 10);
   unsigned long stoul(const string& str, size_t *idx = 0, int base = 10);
   long long stoll(const string& str, size_t *idx = 0, int base = 10);
   unsigned long long stoull(const string& str, size_t *idx = 0, int base = 10);

   float stof(const string& str, size_t *idx = 0);
   double stod(const string& str, size_t *idx = 0);
   long double stold(const string& str, size_t *idx = 0);

   string to_string(int val);
   string to_string(unsigned val);
   string to_string(long val);
   string to_string(unsigned long val);
   string to_string(long long val);
   string to_string(unsigned long long val);
   string to_string(float val);
   string to_string(double val);
   string to_string(long double val);

   The UNICODE version takes or returns a wstring.
*/
#include <string>


int main(){

    std::to_string(1.2); // "1.2"
    std::to_string(123); // "123"

}
