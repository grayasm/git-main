/* It's important to avoid it, but when dealing with legacy code, it can
   be used to extract intermediate calculation values from a library class.
   If the alignment of the external library is mismatched use #pragma pack.
*/

#include <iostream>
#include <memory>

using namespace std;

namespace hidden
{
    class Secret {
    public:
        Secret() { msecret = 42; }
        bool        mboo;
        int         mint;
        std::string sstring;
    private:
        int         msecret;
    };
};

class Replica
{
public:
    int getSecret() { return msecret; }
    bool        mboo;
    int         mint;
    std::string sstring;
private:
    int         msecret;
};

main()
{
    hidden::Secret a;
    Replica *b = reinterpret_cast<Replica*>(&a);
    std::cout << b->getSecret();
}
