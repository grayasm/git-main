/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/

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
