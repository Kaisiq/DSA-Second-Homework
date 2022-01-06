#pragma once
#include <string>

/***
 * Node class representing node of a lcrs tree which has its data, parent, child and brother as private members
 * @param data -> string containing the name of the person who is represented by the node
 * @param child -> pointer to the first child of the Node, the first of his subordinates in the hierarchy
 * @param nextBrother -> pointer to the brother of the node in the lcrs, or so called coworker (they are subordinates of the same person)
 * @param parent -> pointer to the parent of the node in the lcrs (the boss of the person)
 */
class Node{
private:
    std::string data;
    Node* child;
    Node* nextBrother;
    Node* parent;

public:
    /***
     * @brief c-tor with given string and optionally pointers to his child, brother and parent
     * @param name -> name of the person in the hierarchy (string)
     * @param child -> pointer to the first of his children
     * @param next -> pointer to his brother/coworker
     * @param parent -> pointer to his parent/boss
     */
    Node(std::string name, Node* child = nullptr, Node* next = nullptr, Node* parent = nullptr);

    /***
     * @brief default c-tor
     * the data of the node is set to "" by default
     */
    Node();

    /***
     * @brief destructor which deletes the child and brother of the node
     */
    ~Node();

    ///operator= to easily copy the data of one Node to another
    Node& operator= (const Node& other);

    ///setters:
    ///@brief sets the next brother of an Node
    void setNextBrother(Node* next);
    ///@brief sets the first child of an Node
    void setChild(Node* child);
    ///@brief sets the data of an Node (string)
    void setData(std::string data);
    ///@brief sets the parent of an Node
    void setParent(Node* parent);

    ///getters:
    ///@returns pointer to the next brother
    Node* getBrother();
    ///@returns pointer to the child
    Node* getChild();
    ///@returns pointer to the parent
    Node* getParent();
    ///@returns string containing the data of the node
    std::string getData();
};

#include "Node.inl"