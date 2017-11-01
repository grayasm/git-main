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

   See also: http://en.cppreference.com/w/cpp/memory/weak_ptr
   -----------------------------------------------------------------------------

   http://thispointer.com/c11-tutorial/
   http://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/

   To solve the leaking memory issue in binary tree with cyclic reference,
   we have to use the weak_ptr.
   weak_ptr allows sharing but not owning an object. It's object is created
   by a shared_ptr.
*/


#include <iostream>
#include <memory>

using namespace std;

class Node
{
    int value;
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    // change the shared_ptr to weak_ptr
    std::weak_ptr<Node> parent;

    Node(int val): value(val) { cout << __FUNCTION__ << '\n'; }
    ~Node() { cout << __FUNCTION__ << '\n'; }
};


int main()
{
    std::shared_ptr<Node> ptr = std::make_shared<Node>(4);
    ptr->left = std::make_shared<Node>(2);
    ptr->left->parent = ptr;
    ptr->right = std::make_shared<Node>(5);
    ptr->right->parent = ptr;

    std::cout<<"ptr reference count = " << ptr.use_count() << std::endl;
    std::cout<<"ptr->left reference count = " << ptr->left.use_count() << std::endl;
    std::cout<<"ptr->right reference count = " << ptr->right.use_count() << std::endl;
    std::cout<<"ptr->right->parent reference count = " << ptr->right->parent.lock().use_count() << std::endl;
    std::cout<<"ptr->left->parent reference count = " << ptr->left->parent.lock().use_count() << std::endl;

    return 0;
}
