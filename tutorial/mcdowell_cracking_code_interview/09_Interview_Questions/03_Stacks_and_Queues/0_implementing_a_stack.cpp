/*
 */
#include <iostream>
using namespace std;

template<typename T>
class Stack
{
public:
    struct Node
    {
        Node* next;
        T data;
    };

    Stack()
    {
        top = 0;
    }

    void push(T value)
    {
        Node* node = new Node;
        node->next = top;
        node->data = value;
        top = node;
    }

    T pop()
    {
        if (top == 0)
            throw "top is null";

        Node* node = top->next;
        T value = top->data;
        delete top;
        top = node;
        return value;
    }

    T peek()
    {
        if (top == 0)
            throw "top is null";

        return top->data;
    }

    bool empty()
    {
        return (top == 0);
    }
private:
    Node* top;
};


int main()
{
    Stack<int> s;

    for (int i = 0; i < 5; ++i)
        s.push(i + 10);
    while (!s.empty())
        cout << s.pop() << " ";

    return 0;
}
