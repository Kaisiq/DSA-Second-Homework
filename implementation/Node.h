#pragma once
#include <string>

class NodeLL;
class Node{
private:
    std::string data;
    NodeLL* children;
    Node* nextBrother;

public:
    Node(std::string name);
    ~Node();
    Node& operator= (const Node& other);
    bool hasChildren();
    Node* getBrother();
    Node* firstChild();
    Node* lastChild();
    std::string getData();
    void setNextBrother(Node* next);
    void setChildren(NodeLL* children);
    void setData(std::string data);
    int getChildrenSize();
};

#include "Node.inl"