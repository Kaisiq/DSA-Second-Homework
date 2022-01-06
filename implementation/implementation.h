#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include "Node.h"

using std::string;


/***
 * @brief Hierarchy class representing a LCRS tree which contanins all of the workers in the given Hierarchy
 * @param root -> the root of the Hierarchy ( Uspeshnia )
 * @param size -> number of workers in the given Hierarchy
 * @param name -> name of the Hierarchy
 */
class Hierarchy
{
public:
    Hierarchy(Hierarchy&& r) noexcept;
    Hierarchy(const Hierarchy& r);
    Hierarchy(const string& data);
    ~Hierarchy() noexcept;
    void operator=(const Hierarchy&) = delete;

    ///@see printHelper
    string print() const;

    ///@see longest_chain_helper
    ///@returns number representing the longest chain of parent-child in the hierarchy
    int longest_chain() const;

    /***
     * @param name -> name of the person we are searching for
     * @returns true if he is in the Hierarchy
     * @returns false if he isn't
     */
    bool find(const string& name) const;

    ///@brief getter for size
    int num_employees() const;

    /***
     * @brief function that returns how many of the workers have >= (level) subordinates (close and far subordinates)
     * @param level -> the number of subordinates that the worker must have at least to be overloaded
     * @returns the number of overloaded workers
     */
    int num_overloaded(int level = 20) const;

    ///@brief getter for name of the parent
    string manager(const string& name) const;

    /***
     * @brief function that finds out how much subordinates a worker has
     * @param name -> the name of the worker for which we are looking
     * @returns the number of subordinates the worker has
     */
    int num_subordinates(const string& name) const;

    /***
     * @brief calculates the salary of a worker based on his close subordinates and far subordinates
     * @param who -> the name of the person whose salary we are calculating
     * @returns an unsigned integer representing the salary of the person (450*close_subordinates + 50*all_subordinates)
     */
    unsigned long getSalary(const string& who) const;

    /***
     * @brief fire function - removes a person from the Hierarchy
     * @param who -> name of the person to be fired
     * @returns true if the person was found and fired
     * @returns false else
     */
    bool fire(const string& who);

    /***
     * @brief hire function - adds a person to the Hierarchy
     * @param who -> name of the person that has to be added
     * @param boss -> name of his boss in the hierarchy
     * @returns true if the boss was found and the new employee was hired as his subordinate
     * @else @returns false
     */
    bool hire(const string& who, const string& boss);

    /***
     * @brief incorporates the Hierarchy
     * This is done for each team (multiple employees that have the same boss)
     * that has at least two employees; the highest paid employee is selected as the boss of that team
     */
    void incorporate();

    /***
     * This happens to any manager at odd level starting from Uspeshnia;
     * The team of the manager merges with the team of his boss and the current manager is removed
     */
    void modernize();

    /***
     * @brief joins two Hierarchies into new one that contains the workers from both of them
     * @param right -> the other Hierarchy that the current one will be merged with
     * @returns new Hierarchy with the workers from both hierarchies
     */
    Hierarchy join(const Hierarchy& right) const;

    //<------------------------------------If you need it - add more public methods here----------------------------------->

    /***
     * @brief hire function that is executed only for workers that are already in the Hierarchy
     * The function takes the employee and his subordinates and puts him under his new boss in the tree
     * @param who -> the name of the employee which will be rehired
     * @param boss -> his new Bosses' name
     * @returns true if the employee was found and rehired
     * @else @returns false
     */
    bool hire(Node* who, Node* boss);

    /***
     * @brief print helper function
     * @param current -> current node of the tree, used to create recursion
     * @returns string that contains all the workers' names of the hierarchy
     */
    string printHelper(Node* current) const;

    /***
     * @brief helper function for the longest_chain function
     * @param current -> Node* used to create recursion
     * @param maxDepth -> the maximum depth that has been reached by the DFS until now
     * @param currDepth -> the depth of the current instance of the function
     * @returns the longest chain of parent-child relationships in the Hierarchy
     */
    int longest_chain_helper(Node* current, int& maxDepth, int currDepth) const;

    /***
     * @brief finds an employee in the Hierarchy and returns a pointer to his Node
     * @param name -> name of the employee to search for
     * @param current -> Node* used for recursion
     * @returns pointer to the employee if it can be found in the Hierarchy
     * @returns nullptr if the employee can't be found
     */
    Node* find(const string& name, Node* current) const;

    /***
     * @brief finds all the subordinates of the given worker
     * @param current -> Node* used for recursion
     * @param count -> count of the subordinates
     * @returns the count of all subordinates of the worker
     */
    int num_subordinates_helper(Node* current, int& count) const;

    /***
     * @brief finds the subordinates of the given worker only under him
     * @param current -> pointer to the person whose subordinates count we need
     * @returns the count of all close subordinates of the worker
     */
    int num_subordinates_close(Node* current) const;

    /***
     * @brief evaluates the given string and if it is correct it hires the employee to the boss
     * @param toEval -> string that has to be evalued
     */
    void eval(string toEval);

    /***
     * @brief helepr function that finds the overloaded workers starting from the current pointer
     * @param current -> pointer to the person for whom to see if he is overloaded
     * @param level -> the minimum subordinates a person shall have to be overloaded
     * @returns the number of overloaded workers
     */
    int num_overloaded_helper(Node* current, int level = 20) const;

    /***
     * @brief calculates the salary of the given person based on how many subordinates he has
     * @param who -> worker's name
     * @returns the salary of the worker
     */
    unsigned long getSalary(Node* who) const;

    /***
     * @brief calculates in which level (starting from Uspeshnia) the given worker is
     * @param who -> pointer of the worker whose depth we need to calculate
     * @returns the depth of the worker
     */
    int getDepth(Node* who);

    /***
     * @brief default constructor which sets the root to Uspeshnia, size to 1 and the name to ""
     */
    Hierarchy();

    ///@brief setter for the name of the Hierarchy
    void setName(string);
    ///@brief getter for the name of the Hierarchy
    string getName();
    ///@brief checks if the Hierarchy has no workers in it
    bool isEmpty() const;
    ///@brief checks if the given worker is leaf(has no children)
    bool isLeaf(Node* curr);
    ///@brief checks if the given worker has no brothers
    bool hasNoBrothers(Node* curr);
private:
    Node* root;
    size_t size;
    string name;
};

#include "implementation.inl"