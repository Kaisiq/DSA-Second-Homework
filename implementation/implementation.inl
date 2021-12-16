#pragma once

#include "implementation.h"

Hierarchy::Hierarchy(Hierarchy&& r) noexcept{
    this->root = r.root;
    this->size = r.size;
}
Hierarchy::Hierarchy(const Hierarchy& r){
    this->root = r.root;
    this->size = r.size;
}
Hierarchy::Hierarchy(const string& data){
    this->size = 1;
    this->root = new Node(data);
}
Hierarchy::~Hierarchy() noexcept{
    delete this->root;
}

string Hierarchy::print()const{
    Node* iterator = this->root;
    int childrenNum = iterator->getChildrenSize();
    for(int i=0; i<childrenNum; ++i){
        
    }
}

int Hierarchy::longest_chain() const{
    //TODO create
    return 1;
}
bool Hierarchy::find(const string& name) const{
    //TODO create
    return false;
}
int Hierarchy::num_employees() const{
    return size;
}
int Hierarchy::num_overloaded(int level) const{
    return 1;
}

string Hierarchy::manager(const string& name) const{
    return this->root->getData();
}
int Hierarchy::num_subordinates(const string& name) const{
    return 1;
}
unsigned long Hierarchy::getSalary(const string& who) const{
    return 1;
}

bool Hierarchy::fire(const string& who){
    return false;
}
bool Hierarchy::hire(const string& who, const string& boss){
    return false;
}

void Hierarchy::incorporate(){}
void Hierarchy::modernize(){}

Hierarchy Hierarchy::join(const Hierarchy& right) const{
    return *this;
}

