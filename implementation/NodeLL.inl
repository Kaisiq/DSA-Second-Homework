#pragma once

#include "NodeLL.h"



NodeLL::NodeLL(){
    this->size = 0;
    this->first = nullptr;
    this->last = nullptr;
}
NodeLL::~NodeLL(){
    clear();
}
NodeLL& NodeLL::operator=(const NodeLL& other){
    if(this != &other){
        this->first = other.first;
        this->last = other.last;
        this->size = other.size;
    }
    return *this;
}

bool NodeLL::isEmpty(){
    return first == nullptr && size == 0;
}
void NodeLL::clear(){
    while(!isEmpty()){
        pop();
    }
}
Node* NodeLL::getFirst(){
    return this->first->data;
}
Node* NodeLL::getLast(){
    return this->last->data;
}
void NodeLL::push(Node* node){
    Box* newBox = new Box(node);
    if(isEmpty()){
        this->first = this->last = newBox;
    }
    this->last->next = newBox;
    this->last = newBox;
    size++;
}
void NodeLL::pop(){
    if(isEmpty()) return;
    Box* temp = this->first;
    this->first = first->next;
    delete temp;
    size--;
}

size_t NodeLL::getSize(){
    return this->size;
}