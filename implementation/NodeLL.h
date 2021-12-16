#pragma once

class Node;
class NodeLL{
private:
    class Box{
    public:
        Node* data;
        Box* next;

    public:
        Box(Node* data, Box* nextBox = nullptr)
            : data(data), next(nextBox){}
        bool hasNext() const{
            return next != nullptr;
        }
    };

public:
    size_t size;
    Box* first;
    Box* last;

    NodeLL();
    ~NodeLL();
    NodeLL &operator=(const NodeLL& other);

    bool isEmpty();
    void clear();
    Node* getFirst();
    Node* getLast();
    void push(Node*);
    void pop();
    size_t getSize();
};

#include "Node.h"
#include "NodeLL.inl"