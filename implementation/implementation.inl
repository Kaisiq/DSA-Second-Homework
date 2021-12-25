#pragma once

#include "implementation.h"
#include <queue>

Hierarchy::Hierarchy(Hierarchy&& r) noexcept{
    this->root = r.root;
    this->size = r.size;
}
Hierarchy::Hierarchy(const Hierarchy& r){
    this->root = r.root;
    this->size = r.size;
}
Hierarchy::Hierarchy(const string& data){
    if(data != "") {
        this->size = 1;
        this->root = new Node("Uspeshnia");
        eval(data);
    }
    else{
        this->size = 0;
        this->root = nullptr;
    }
}

void Hierarchy::eval(string toEval){
    int countLettersToRemove = 0;
    int i=0;

    //<---------find and copy boss-------------->
    while(toEval[i] && (toEval[i]==' ' || toEval[i] == '-' || toEval[i]=='\n')){
        i++;
    }
    countLettersToRemove = i;
    while(toEval[i] && toEval[i] != ' ' && toEval[i] != '-' && toEval[i]!= '\n'){
        i++;
    }
    std::string boss = "";
    for(int j=countLettersToRemove; j<i; j++){
        boss += toEval[j];
    }
    //<---------find and copy boss-------------->

    int countMinus = 0;
    while(toEval[i] && (toEval[i]==' ' || toEval[i] == '-' || toEval[i]=='\n')){
        if(toEval[i] == '-'){
            countMinus++;
        }
        i++;
    }
    if(countMinus == 0) {
        throw std::runtime_error("Wrong Format");
    }

    //<---------find and copy employee-------------->
    countLettersToRemove = i;
    while(toEval[i] && toEval[i] != ' ' && toEval[i] != '-' && toEval[i]!= '\n'){
        i++;
    }
    std::string employee = "";
    for(int j=countLettersToRemove; j<i; j++){
        employee += toEval[j];
    }
    //<---------find and copy employee-------------->


    while(toEval[i] && (toEval[i]==' ' || toEval[i]=='\n')){
        i++;
    }
    countLettersToRemove = i;


    hire(employee, boss);

    toEval = toEval.substr(i, toEval.length());
    if(!toEval.empty()){
        eval(toEval);
    }
}



Hierarchy::~Hierarchy() noexcept{
    delete this->root;
}

string Hierarchy::print()const{
    return Hierarchy::printHelper(root);
}

string Hierarchy::printHelper(Node* current) const{
    std::string result = "";
    if(!current){
        return result;
    }

    std::queue<Node*> q;

    Node* child = current->getChild();
    result += current->getData() + "-" + child->getData() + "\n";
    q.push(child);
    while(child->getBrother()){
        child = child->getBrother();
        result += current->getData() + "-" + child->getData() + "\n";
    }

    while(!q.empty()){
        current = q.front();
        q.pop();
        while(current){
            child = current->getChild();
            if (child) q.push(child);
            while(child){
                result += current->getData() + "-" + child->getData() + "\n";
                child = child->getBrother();
            }
            current = current->getBrother();
        }
    }
    return result;
}


int Hierarchy::longest_chain() const{
    int mD = 0;
    return longest_chain_helper(this->root, mD,0);
}

bool Hierarchy::isEmpty() const{
    return size == 0 && root == nullptr;
}


int Hierarchy::longest_chain_helper(Node* current, int& maxDepth, int currDepth) const{
    if(this->isEmpty()) return 0;
    if(!current){
        return maxDepth;
    }
    if(currDepth == 0){
        currDepth = 1;
    }
    if(maxDepth < currDepth){
        maxDepth = currDepth;
    }
    while(current){
        if(current->getChild()) {
            longest_chain_helper(current->getChild(), maxDepth, currDepth+1);
        }
        current = current->getBrother();
    }
    return maxDepth;
}


bool Hierarchy::find(const string& name) const{
    return find(name, this->root) != nullptr;
}

Node* Hierarchy::find(const string& name, Node* current) const{
    if(!current){
        return nullptr;
    }
    while(current){
        if(current->getData() == name){
            return current;
        }
        if(current->getChild()) {
            if(Node* res = find(name, current->getChild())){
                return res;
            }
        }
        current = current->getBrother();
    }
    return nullptr;
}


int Hierarchy::num_employees() const{
    return size;
}
int Hierarchy::num_overloaded(int level) const{
    return num_overloaded_helper(this->root, level);
}

int Hierarchy::num_overloaded_helper(Node* current, int level) const{
    int overloaded = 0;
    int zero = 0;
    while(current) {
        if (num_subordinates_helper(current->getChild(), zero) >= level) {
            overloaded++;
        }
        if(current->getChild()){
            overloaded += num_overloaded_helper(current->getChild(), level);
        }
        current = current->getBrother();
    }
    return overloaded;
}

string Hierarchy::manager(const string& name) const{
    Node* current = find(name,root);
    if(current){
        Node* hisParent = current->getParent();
        if(hisParent){
            return hisParent->getData();
        }
    }
    return "";
}

int Hierarchy::num_subordinates(const string& name) const{
    Node* current = find(name, root);
    if(!current){
        return -1;
    }
    if(current && current->getChild()) {
        return num_subordinates_close(current->getChild());
    }
    return 0;
}

int Hierarchy::num_subordinates_helper(Node* current, int& count) const{
    if(!current){
        return 0;
    }

    while(current){
        count++;
        if(current->getChild()){
            num_subordinates_helper(current->getChild(), count);
        }
        current = current->getBrother();
    }
    return count;
}

int Hierarchy::num_subordinates_close(Node* current) const{
    int count = 0;
    if(!current){
        return count;
    }
    count++;
    while(current && current->getBrother()){
        current = current->getBrother();
        count++;
    }
    return count;
}


unsigned long Hierarchy::getSalary(const string& who) const{
    Node* current = find(who,root);
    if(!current){
        return -1;
    }
    int zero = 0;
    int sum = 450* num_subordinates(who);
    sum += 50 * num_subordinates_helper(current->getChild(), zero);
    return sum;
}
unsigned long Hierarchy::getSalary(Node* who) const{
    if(!who){
        return -1;
    }
    int zero = 0;
    int sum = 450* num_subordinates_helper(who, zero);
    zero = 0;
    sum += 50 * num_subordinates_helper(who->getChild(), zero);
    return sum;
}


bool Hierarchy::isLeaf(Node* curr){
    return curr->getChild() == nullptr;
}
bool Hierarchy::hasNoBrothers(Node* curr){
    return curr->getBrother() == nullptr && curr->getParent()->getChild() == curr;
}



//TODO: fix ~Node
bool Hierarchy::fire(const string& who){
    Node* toDelete = find(who,root);
    if(!toDelete) return false;


    //Case 0: is Uspeshnia
    if(!toDelete->getParent()){
        return false;
    }

    //Case 1 : is Leaf, has no brothers
    if(isLeaf(toDelete) && hasNoBrothers(toDelete)){
        toDelete->getParent()->setChild(nullptr);
//        delete toDelete;
        size--;
        return true;
    }

    //case 2: is Leaf, has brothers
    else if(isLeaf(toDelete)){
        Node* prevBrother = toDelete->getParent()->getChild();
        while(prevBrother->getBrother() != toDelete){
            prevBrother = prevBrother->getBrother();
        }
        if(prevBrother == toDelete){
            toDelete->getParent()->setChild(toDelete->getBrother());
            size--;
            return true;
        }
        if(toDelete->getBrother()){
            prevBrother->setNextBrother(toDelete->getBrother());
        }
        else{
            prevBrother->setNextBrother(nullptr);
        }
//        delete toDelete;
        size--;
        return true;
    }

    //case 3: is not leaf, has no brothers => has child
    else if(hasNoBrothers(toDelete)){
        toDelete->getParent()->setChild(toDelete->getChild());
//        delete toDelete;
        size--;
        return true;
    }

    //case 4: is not leaf, has brothers
    else{
        if(toDelete == toDelete->getParent()->getChild()) {
            Node* child = toDelete->getChild();
            toDelete->getParent()->setChild(child);
            while (child->getBrother()) {
                child = child->getBrother();
            }
            child->setNextBrother(toDelete->getBrother());
//            delete toDelete;
            size--;
            return true;
        }
        Node* child = toDelete->getChild();
        Node* prevBrother = toDelete->getParent()->getChild();
        while(prevBrother->getBrother() != toDelete){
            prevBrother = prevBrother->getBrother();
        }
        prevBrother->setNextBrother(child);
        while (child->getBrother()) {
            child = child->getBrother();
        }
        child->setNextBrother(toDelete->getBrother());
        //            delete toDelete;
        size--;
        return true;
    }
}

bool Hierarchy::hire(const string& who, const string& boss){
    Node* newEmployee = find(who, root);
    Node* hisBoss = find(boss, root);

    if(newEmployee == root){
        return false;
    }

    if(newEmployee && newEmployee->getParent() != hisBoss){
        //case 1: boss has no children, employee has no brothers
        if(hisBoss->getChild() == nullptr && newEmployee->getParent()->getChild() == newEmployee && newEmployee->getBrother() == nullptr){
            hisBoss->setChild(newEmployee);
            newEmployee->getParent()->setChild(nullptr);
            newEmployee->setParent(hisBoss);
            return true;
        }
        //case 2: boss has no children, employee has brothers
        else if(hisBoss->getChild() == nullptr){
            Node* prevBrotherOfEmployee = newEmployee->getParent()->getChild();
            while(prevBrotherOfEmployee->getBrother() && prevBrotherOfEmployee->getBrother() != newEmployee){
                prevBrotherOfEmployee = prevBrotherOfEmployee->getBrother();
            }
            if(prevBrotherOfEmployee->getBrother() != newEmployee){
                newEmployee->getParent()->setChild(newEmployee->getBrother());
            }
            else{
                prevBrotherOfEmployee->setNextBrother(newEmployee->getBrother());
            }
            newEmployee->setNextBrother(nullptr);
            hisBoss->setChild(newEmployee);
            newEmployee->setParent(hisBoss);
            return true;
        }

        //case 3: boss has children, employee has brothers
        else{
            Node* prevBrotherOfEmployee = newEmployee->getParent()->getChild();
            while(prevBrotherOfEmployee->getBrother() && prevBrotherOfEmployee->getBrother() != newEmployee){
                prevBrotherOfEmployee = prevBrotherOfEmployee->getBrother();
            }
            if(prevBrotherOfEmployee->getBrother() != newEmployee){
                newEmployee->getParent()->setChild(newEmployee->getBrother());
            }
            else{
                prevBrotherOfEmployee->setNextBrother(newEmployee->getBrother());
            }
            Node* firstChildOfNewParent = hisBoss->getChild();
            while(firstChildOfNewParent->getBrother()){
                firstChildOfNewParent = firstChildOfNewParent->getBrother();
            }
            firstChildOfNewParent->setNextBrother(newEmployee);
            newEmployee->setNextBrother(nullptr);
            newEmployee->setParent(hisBoss);
            return true;
        }
    }
    else if(newEmployee && newEmployee->getParent() == hisBoss){
        return true;
    }


    if(hisBoss == nullptr){
        throw std::runtime_error("The employee's boss isn't in the hierarchy");
    }
    if(hisBoss){
        Node* toHire = new Node(who);
        Node* bossChild = hisBoss->getChild();
        if(bossChild) {
            while (bossChild->getBrother()) {
                bossChild = bossChild->getBrother();
            }
            bossChild->setNextBrother(toHire);
        }
        else {
            hisBoss->setChild(toHire);
        }
        toHire->setParent(hisBoss);
        size++;
        return true;
    }
}

void Hierarchy::incorporate(){
    incorporate_helper(root);
}

void Hierarchy::incorporate_helper(Node *curr) {
    if(curr->getChild()){
        incorporate_helper(curr->getChild());
    }
    if(!curr->getParent()){
        return;
    }
    if(hasNoBrothers(curr)) return;
    Node* brother;
    while(curr){
            brother = curr->getBrother();
        while(brother) {
            if (getSalary(curr->getData()) > getSalary(brother->getData())){
                brother = brother->getBrother();
            }
            break;
        }
        if(!curr->getBrother()){
            break;
        }
        curr = curr->getBrother();
    }
    if(getSalary(curr) == getSalary(curr->getParent()->getChild())){
        curr = curr->getParent()->getChild();
    }
    brother = curr->getParent()->getChild();
    if(brother == curr) brother = brother->getBrother();
    hire(brother->getData(), curr->getData());
    return;
}

void Hierarchy::modernize(){}

Hierarchy Hierarchy::join(const Hierarchy& right) const{
    return *this;
}

