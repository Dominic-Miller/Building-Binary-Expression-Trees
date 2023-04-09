#include <iostream>
#include <stack>
#include <string>
using namespace std;

class BET {
    public:

        BET(); //Creates an empty tree
        BET(const string& postfix); //Builds a postfix tree using buildFromPostfix function
        BET(const BET& b); //Creates a deep copy of the tree using clone function
        ~BET(); //Destructor, calls makeEmpty function
        bool buildFromPostfix(const string& postfix); //Builds a tree based upon postfix expression
        const BET & operator=(const BET& b); //Makes a deep copy, calls makeEmpty function then clone function
        void printInfixExpression() const; //Prints out infix expression using private recursive function
        void printPostfixExpression() const; //Prints out postfix expression using private recursive function
        size_t size() const; //Returns number of nodes in tree using private recursive function
        size_t leaf_nodes() const; //Returns number of leaf nodes in the tree using private recursive function
        bool empty() const; //Checks if the tree is empty

    private:

        struct BinaryNode {

            string element;
            BinaryNode* left; //Pointer to left child
            BinaryNode* right; //Pointer to right child

            BinaryNode(const string& theElement, BinaryNode* lt, BinaryNode* rt) 
                : element{theElement}, left{lt}, right{rt} {}

            BinaryNode(string&& theElement, BinaryNode* lt, BinaryNode* rt)
                : element{std::move(theElement)}, left{lt}, right{rt} {}
        };

        BinaryNode* root;
        string printInfixExpression(BinaryNode* n) const;
        void makeEmpty(BinaryNode* &t);
        BinaryNode* clone(BinaryNode* t) const;
        void printPostfixExpression(BinaryNode* n) const;
        size_t size(BinaryNode* t) const;
        size_t leaf_nodes(BinaryNode* t) const;

};
