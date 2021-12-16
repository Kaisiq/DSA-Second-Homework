#pragma once
#include <string>

class NodeLL;
class Node{
private:
    std::string data;
    NodeLL* children;
    Node* nextBrother;

public:
    Node(std::string name, NodeLL* children, Node* brother);
    ~Node();
    Node& operator= (const Node& other);
    bool hasChildren();
    Node* getBrother();
    Node* firstChild();
    Node* lastChild();
    std::string getData();
};