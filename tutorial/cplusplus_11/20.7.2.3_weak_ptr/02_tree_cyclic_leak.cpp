/* http://thispointer.com/c11-tutorial/
   http://thispointer.com/shared_ptr-binary-trees-and-the-problem-of-cyclic-references/

   If we add to the previous binary tree example another small requirement
   that each node will contain a pointer to parent's node, then it will cause
   problems with shared_ptr.
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
	std::shared_ptr<Node> parent;

	Node(int val) : value(val) { cout << __FUNCTION__ << '\n'; }
	~Node() { cout << __FUNCTION__<< '\n'; }
};


int main()
{
	std::shared_ptr<Node> p2 = std::make_shared<Node>(4);
	p2->left = std::make_shared<Node>(2);
	p2->left->parent = p2;
	p2->right = std::make_shared<Node>(5);
	p2->right->parent = p2;

	cout << "p2 reference count=" << p2.use_count() << '\n';
	cout << "p2->left reference count=" << p2->left.use_count() << '\n';
	cout << "p2->right reference count=" << p2->right.use_count() << '\n';

	return 0;
}
