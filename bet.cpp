#include "bet.h"
#include <iostream>
#include <stack>
#include <string>
using namespace std;

/*
PUBLIC FUNCTIONS
*/


BET::BET() {
    root = nullptr; //creates an empty binary tree with root
}

BET::BET(const string& postfix) {
    if (buildFromPostfix(postfix)) { //sets root equal to final binary expression tree
        cout << "Successfully built the tree given " << postfix << endl;
    }
    else {
        cout << "Cannot build the tree based on " << postfix << "\n";
    }
}

BET::BET(const BET& b) {
    root = clone(b.root);
}

BET::~BET() {
    makeEmpty(root);
}

bool BET::buildFromPostfix(const string& postfix) {

    makeEmpty(root); //if not already empty
    stack<BinaryNode*> postStack; //creates an empty stack of type pointer to a BinaryNode
    BinaryNode *node, *rightNode, *leftNode; //creates three empty BinaryNodes

    int numOperands = 0;
    int numOperators = 0;

    for (int x = 0; x < postfix.size(); x++) { //iterate through expression
        string s = std::string(1, postfix[x]);
        if ((postfix[x] != '+') && (postfix[x] != '-') && (postfix[x] != '/') && (postfix[x] != '*') 
        && (postfix[x] != ' ')) { //if operand
            if (postfix[x + 1] != ' ') { //if multiple digit number (next is operand)
                s += postfix[x + 1]; //make the numbers one
                x++; //incriment x
            }
            node = new BinaryNode(s, nullptr, nullptr);
            postStack.push(node);
            numOperands += 1; //count num of operands
        }
        else if (postfix[x] != ' ') { //if operator
            rightNode = postStack.top(); //right is the top element
            postStack.pop();
            leftNode = postStack.top(); //left is the next element
            postStack.pop();
            node = new BinaryNode(s, leftNode, rightNode);
            postStack.push(node);
            numOperators += 1;
        }
    }

    root = postStack.top(); //top of stack is final binary expression tree

    //if problem with the expression
    if ((numOperands - 1 != numOperators) || (numOperators == 0)) {
        makeEmpty(root);
        return false;
    }
    //if everything is good
    return true;
}

const BET& BET::operator= (const BET& b) {
    makeEmpty(root);
    root = clone(b.root);
    return *this;
}

void BET::printInfixExpression() const {
    //inorder traversal of BET will give infix expression
    if (empty()) {
        cout << "Empty Tree\n";
    }
    else {
        cout << printInfixExpression(root) << endl;
    }
}

void BET::printPostfixExpression() const {
    //postorder traversal of BET will give postfix expression
    if (empty()) {
        cout << "Empty Tree\n";
    }
    else {
        printPostfixExpression(root);
        cout << endl;
    }
}

size_t BET::size() const {
    return size(root);
}

size_t BET::leaf_nodes() const {
    return leaf_nodes(root);
}

bool BET::empty() const {
    if (root == nullptr) {
        return true;
    }
    return false;
}


/*
PRIVATE HELPER FUNCTIONS
*/


string BET::printInfixExpression(BinaryNode* n) const {
    //inorder traversal of BET will give infix expression
    string expression;
    if (n != nullptr) {
        expression = printInfixExpression(n->left); //recurse left first
        if ((n->element == "*" && (n->left->element == "+" || n->left->element == "-")) 
        || (n->element == "/" && (n->left->element == "+" || n->left->element == "-" || n->left->element == "*"))) {
            expression = "( " + expression + ") " + n->element + " "; //add parentheses
        }
        else {
            expression += n->element + " ";
        }

        if ((n->element == "*" && (n->right->element == "+" || n->right->element == "-")) 
        || (n->element == "/" && (n->right->element == "+" || n->right->element == "-" || n->left->element == "*"))) {
            expression += "( " + printInfixExpression(n->right) + ") "; //add parentheses
        }
        else {
            expression += printInfixExpression(n->right); //recurse right
        }
    }
    return expression;
}

void BET::makeEmpty(BinaryNode* &t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

BET::BinaryNode* BET::clone(BinaryNode* t) const {
    if (t != nullptr) {
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
    return nullptr;
}

void BET::printPostfixExpression(BinaryNode* n) const {
    //postorder traversal of BET will give postfix expression
    if (n != nullptr) {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        cout << n->element << " ";
    }
}

size_t BET::size(BinaryNode* t) const {
    size_t num = 0;
    if (t != nullptr) {
        num += size(t->left);
        num += size(t->right);
        return (1 + num); //add on root node
    }
    return 0; //empty tree
}

size_t BET::leaf_nodes(BinaryNode* t) const {
    if (t != nullptr && t->left == nullptr && t->right == nullptr) {
        return 1; //just root node
    }
    else if (t != nullptr) {
        return (leaf_nodes(t->left) + leaf_nodes(t->right));
    }
    return 0; //empty tree
}
