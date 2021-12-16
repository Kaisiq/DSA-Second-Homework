#include "Node.h"

Node::Node(std::string name): data(name){
    this->children = nullptr;
    this->nextBrother = nullptr;
}
Node::~Node(){
    delete this->children;
    delete this->nextBrother;
}
Node& Node::operator= (const Node& other){
    if(this != &other){
        this->data = other.data;
        this->nextBrother = other.nextBrother;
        this->children = other.children;
    }
    return *this;
}

bool Node::hasChildren(){
    return !this->children->isEmpty();
}
Node* Node::getBrother(){
    return this->nextBrother;
}
Node* Node::firstChild(){
    return this->children->getFirst();
}
Node* Node::lastChild(){
    return this->children->getLast();
}
std::string Node::getData(){
    return this->data;
}


void Node::setNextBrother(Node* next){
    delete this->nextBrother;
    this->nextBrother = next;
}
void Node::setChildren(NodeLL* children){
    delete this->children;
    this->children = children;
}
void Node::setData(std::string data){
    this->data = data;
}

int Node::getChildrenSize(){
    return this->children->getSize();
}