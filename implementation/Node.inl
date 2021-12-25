#include "Node.h"

Node::Node(std::string name){
    this->data = name;
    this->child = nullptr;
    this->nextBrother = nullptr;
    this->parent = nullptr;
}

Node::Node(){
    this->data = "";
    this->child = nullptr;
    this->nextBrother = nullptr;
    this->parent = nullptr;
}

Node::~Node(){
    if(this->child  != NULL)
        delete this->child;
    if(this->nextBrother != NULL)
        delete this->nextBrother;
}
Node& Node::operator= (const Node& other){
    if(this != &other){
        this->data = other.data;
        this->nextBrother = other.nextBrother;
        this->child = other.child;
        this->parent = other.parent;
    }
    return *this;
}

Node* Node::getChild(){
    return this->child;
}
Node* Node::getBrother(){
    return this->nextBrother;
}

std::string Node::getData(){
    return this->data;
}

Node* Node::getParent(){
    return this->parent;
}

void Node::setParent(Node *parent) {
    if(this->parent)
        delete this->parent;
    this->parent = parent;
}

void Node::setNextBrother(Node* next){
    if(this->nextBrother)
        delete this->nextBrother;
    this->nextBrother = next;
}
void Node::setChild(Node* child){
    if(this->child)
        delete this->child;
    this->child = child;
}
void Node::setData(std::string data){
    this->data = data;
}
