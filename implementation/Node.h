#pragma once
#include <string>

class Node{
private:
    std::string data;
    Node* child;
    Node* nextBrother;
    Node* parent;

public:
    Node(std::string name);
    Node();
    ~Node();
    Node& operator= (const Node& other);
    Node* getBrother();
    Node* getChild();
    Node* getParent();
    std::string getData();
    void setNextBrother(Node* next);
    void setChild(Node* child);
    void setData(std::string data);
    void setParent(Node* parent);
};

#include "Node.inl"