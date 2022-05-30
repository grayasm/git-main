/* Header: <memory>
   Signature: constexpr weak_ptr() noexcept;
                        weak_ptr(const weak_ptr& x) noexcept;
              template<class U>
                        weak_ptr(const weak_ptr<U>& x) noexcept;
              template<class U>
                        weak_ptr(const shared_ptr<U>& x) noexcept;

   Description:
      - weak_ptr is a smart pointer that holds a non-owning "weak" reference
        to an object that is managed by std::shared_ptr. It must be converted
        to std::shared_ptr in order to access the referenced object.
      - weak_ptr is used to break circular references of std::shared_ptr
      - if the original std::shared_ptr is destroyed, the object's lifetime is
        extended until the temporary std::shared_ptr is destroyed as well

   http://thispointer.com/c11-tutorial
   http://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references

   Main advantage of shared_ptr is that it automatically releases the associated
   memory when not used anymore.
   But if we don't use shared_ptr carefully, then this advantage can turn into
   a disanvantage. Let's look how.

   Below we have a normal binary tree, that does not leak memory.
   In the next 2 examples, one BTree will leak memory and one will fix this
   problem by using weak_ptr.
*/


#include <iostream>
#include <memory>

using namespace std;

class Node
{
    int value;
public:
    std::shared_ptr<Node> leftPtr;
    std::shared_ptr<Node> rightPtr;

    Node(int val) : value(val)
    {
        cout << __FUNCTION__ << '\n';
    }
    ~Node()
    {
        cout << __FUNCTION__ << '\n';
    }
};


int main()
{
    std::shared_ptr<Node> ptr = std::make_shared<Node>(4);
    ptr->leftPtr = std::make_shared<Node>(2);
    ptr->rightPtr = std::make_shared<Node>(5);

    return 0;
}
