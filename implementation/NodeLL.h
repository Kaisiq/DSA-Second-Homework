#pragma once
#include "Node.h"

class NodeLL{
private:
    class Box{
    public:
        Node data;
        Box* next;

    public:
        Box(const Node data, Box* nextBox = nullptr)
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
    Box* getFirst();
    Box* getLast();
    Box* push(const Node);
    void pop();

};