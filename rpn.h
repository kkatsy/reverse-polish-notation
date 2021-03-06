/*
 * Name: Katya Katsy
 * Email: kkatsy@ucdavis.edu
*/

#include <string>
#include <list>
#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

/* check if a string is a valid operator symbol */
bool is_operator (string &a_string){
    string operator_list[] = {"+", "-","*","/", "**","<", ">"};

    bool in_list = false;
    for (auto const &i: operator_list){
        if(i == a_string) {
            in_list = true;
        }
    }

    return in_list;
}


/* perform a numeric operation given an operand and stack of operators */
void perform_operation(string &operand, list<double>& numStack){

    double result;
    if (operand == "+"){
        // addition
        double operator_top = numStack.back();
        numStack.pop_back();
        double operator_bottom = numStack.back();
        numStack.pop_back();
        result = operator_bottom + operator_top;

    } else if (operand == "-") {
        // subtraction
        double operator_top = numStack.back();
        numStack.pop_back();
        double operator_bottom = numStack.back();
        numStack.pop_back();
        result = operator_bottom - operator_top;

    } else if (operand == "*"){
        // multiplication
        double operator_top = numStack.back();
        numStack.pop_back();
        double operator_bottom = numStack.back();
        numStack.pop_back();
        result = operator_bottom * operator_top;

    } else if (operand == "/"){
        // division
        double operator_top = numStack.back();
        numStack.pop_back();
        double operator_bottom = numStack.back();
        numStack.pop_back();

        if(operator_top == 0.0){
            throw std::invalid_argument( "Division by zero!" );
        }
        result = operator_bottom / operator_top;

    } else if (operand == "**") {
        // exponent
        double operator_top = numStack.back();
        numStack.pop_back();
        double operator_bottom = numStack.back();
        numStack.pop_back();

        if(operator_bottom == 0.0 && operator_top == 0.0){
            throw std::invalid_argument( "Exponentiation of zero!" );
        }
        result = pow(operator_bottom, operator_top);

    } else if (operand == "<"){
        // ceiling
        double operator_top = numStack.back();
        numStack.pop_back();
        result = ceil(operator_top);

    } else if (operand == ">"){
        // floor
        double operator_top = numStack.back();
        numStack.pop_back();
        result = floor(operator_top);

    } else {
        // invalid operand
        throw std::invalid_argument( "Invalid operand!" );
    }

    numStack.push_back(result);
}


/* execute a given reverse polish notation string */
double rpn(string *strs, int strs_length) {

    double result = 0;
    list<double> numberStack;

    // iterate thru elements in reverse polish notation string
    for(int i = 0; i < strs_length; i++){

        // if string is not an operator, add to stack
        if(!is_operator(strs[i])){

            // add to stack
            numberStack.push_back(stod(strs[i]));

        // if string is an operator, perform operation on vals in stack
        } else if(is_operator(strs[i]))  {

            // perform operation on stack
            if((strs[i] == "<" || strs[i] == ">") && i > 1){
                perform_operation(strs[i], numberStack);
            } else if(i > 2){
                perform_operation(strs[i], numberStack);
            } else {
                throw std::invalid_argument( "Not enough values to perform operation!" );
            }

        } else {
            throw std::invalid_argument( "Invalid rph element!" );
        }
    }

    return numberStack.front();
}

/* Node containing data element + left and right child nodes */
struct Node {
    string data;
    struct Node *left, *right;

    // constructor #1
    Node(string d, Node *l, Node *r){
        data = std::move(d);
        left = l;
        right = r;
    }

    // constructor #2
    Node(){
        data = " ";
        left = nullptr;
        right = nullptr;
    }

    // return if node is a leaf node
    bool is_leaf_node() const {
        if (left == nullptr && right == nullptr){
            return true;
        } else {
            return false;
        }
    }
};

/* recursively print an abstract syntax tree given a binary tree */
void print_ast(Node* root, int level){

    // continue recursion until reach leaves of tree
    if (root != nullptr) {

        for(int i = 0; i < level; i++){
            cout << "\t";
        }

        if(!root->is_leaf_node()){
            cout << "(";
        }

        cout << root->data << "\n";

        level++;

        // recursive calls on left and right child
        print_ast(root->left, level);
        print_ast(root->right, level);

        if(!root->is_leaf_node()){
            for(int i = 0; i < level - 1; i++){
                cout << "\t";
            }
            cout << ")" << "\n";
        }
    }
}

/* create + print the abstract syntax tree of a given reverse polish notation */
void ast(string *strs, int strs_length){
    list<Node*> stack;

    for(int i = 0; i < strs_length; i++){
        if (is_operator(strs[i]) && strs[i]!="<" && strs[i]!=">"){
            // if string is an operator with two operands:

            Node *rightElem = stack.back();
            stack.pop_back();

            Node *leftElem = stack.back();
            stack.pop_back();

            Node *newNode;
            newNode = new Node(strs[i], leftElem, rightElem);

            stack.push_back(newNode);

        } else {
            // if string is not an operator:

            Node *newNode;
            newNode = new Node();

            newNode->data = strs[i];

            stack.push_back(newNode);
        }
    }

    // print the ast using the binary tree stack of nodes
    print_ast(stack.front(), 0);
}