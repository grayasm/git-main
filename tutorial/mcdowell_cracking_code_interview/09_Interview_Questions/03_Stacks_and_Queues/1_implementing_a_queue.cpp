/*
 */
#include <iostream>
using namespace std;

template<typename T>
class Queue
{
public:
    struct Node
    {
        Node* next;
        T data;
    };

    Queue()
    {
        first = 0;
        last = 0;
    }

    void add(T value)
    {
        Node* node = new Node;
        node->data = value;

        if (last == 0)
        {
            last = node;
            first = last;
        }
        else
        {
            last->next = node;
            last = node;
        }
    }

    T remove()
    {
        if (first == 0)
            throw "queue is empty";

        Node* node = first->next;
        T value = first->data;

        delete first;
        first = node;
        return value;
    }

    T peek()
    {
        if (last == 0)
            throw "queue is empty";
        return last->data;
    }

    bool isEmpty()
    {
        return (first == 0);
    }

private:
    Node* last;
    Node* first;
};


int main()
{
    Queue<int> q;
    for (int i = 0; i < 5; i++)
        q.add(i + 10);

    while(!q.isEmpty())
        cout << q.remove() << " ";

    return 0;
}
