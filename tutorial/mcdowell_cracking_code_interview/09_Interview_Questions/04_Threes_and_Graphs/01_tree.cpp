/*
 */

template<typename T>
class Tree
{
public:
    struct Node
    {
        Node** children;
        T data;
    };

    Tree()
    {
        root = 0;
    }

    void add(T value)
    {
        if (root == 0)
        {
            root = new Node;
            root->children = new Node*[2];
            root->children[0] = 0;
            root->children[1] = 0;
            root->data = value;
        }
        else
        {
            
        }
    }


private:
    void add(Node* under, T value)
    {
        if (under->children[0].data > value)
            return add(under->children[0], value);

        if (under->children[1].data > value)
            return add(under->children[1], value);

        Node* great = under->children[1];
        Node* node = new Node;
        node->children = new Node*[2];
        node->children[0] = great;
        node->children[1] = 0;

        under->children[1] = node;
    }

    Node* root;
};
