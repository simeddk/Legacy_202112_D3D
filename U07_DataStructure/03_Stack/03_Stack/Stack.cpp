

#include "Stack.h"

Stack::~Stack()
{
    while (IsEmpty() == false)
        DestroyNode(Pop());

    list = nullptr;
    top = nullptr;
}

void Stack::Push(Node* node)
{
    if (list == nullptr)
        list = node;
    else
    {
        Node* tail = list;
        while (tail->Next != nullptr)
            tail = tail->Next;

        tail->Next = node;
    }

    top = node;
}

Node* Stack::Pop()
{
    Node* temp = top;

    if (list == top)
    {
        list = nullptr;
        top = nullptr;
    }
    else
    {
        Node* tail = list;
        while (tail != nullptr && tail->Next != top)
            tail = tail->Next;

        top = tail;
        tail->Next = nullptr;
    }

    return temp;
}

int Stack::Size()
{
    int count = 0;

    Node* current = list;
    while (current != nullptr)
    {
        current = current->Next;
        count++;
    }

    return count;
}

Node* Stack::CreateNode(string data)
{
    Node* node = new Node();
    node->Data = data;
    node->Next = nullptr;

    return node;
}

void Stack::DestroyNode(Node* node)
{
    delete node;
    node = nullptr;

}
