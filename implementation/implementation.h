#pragma once
#include <string>
#include <iostream>
#include "Node.h"

using std::string;

class Hierarchy
{
public:
    Hierarchy(Hierarchy&& r) noexcept;
    Hierarchy(const Hierarchy& r);
    Hierarchy(const string& data);
    ~Hierarchy() noexcept;
    void operator=(const Hierarchy&) = delete;

    string print()const;

    int longest_chain() const;
    bool find(const string& name) const;
    int num_employees() const;
    int num_overloaded(int level = 20) const;

    string manager(const string& name) const;
    int num_subordinates(const string& name) const;
    unsigned long getSalary(const string& who) const;

    bool fire(const string& who);
    bool hire(const string& who, const string& boss);

    void incorporate();
    void modernize();

    Hierarchy join(const Hierarchy& right) const;

    //If you need it - add more public methods here
    string printHelper(Node* current) const;
    int longest_chain_helper(Node* current, int& maxDepth, int currDepth) const;
    Node* find(const string& name, Node* current) const;
    int num_subordinates_helper(Node* current, int& count) const;
    int num_subordinates_close(Node* current) const;
    bool isEmpty() const;
    void eval(string toEval);
    int num_overloaded_helper(Node* current, int level = 20) const;
    bool isLeaf(Node* curr);
    bool hasNoBrothers(Node* curr);
    void incorporate_helper(Node* curr);
    unsigned long getSalary(Node* who) const;
private:
    Node* root;
    size_t size;
};

#include "implementation.inl"