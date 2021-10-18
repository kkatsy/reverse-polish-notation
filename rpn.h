#include <string>
#include <list>
#include <iostream>
#include <cmath>
#include <utility>

using namespace std;


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


double perform_operation(string &operand, list<double>& numStack){
    double operator_top = numStack.back();
    numStack.pop_back();

    double operator_bottom = numStack.back();
    numStack.pop_back();

    std::cout << operator_top << " " << operator_bottom << endl;

    double result = 0;
    if (operand == "+"){
        // addition
        result = operator_bottom + operator_top;

    } else if (operand == "-") {
        // subtraction
        result = operator_bottom - operator_top;

    } else if (operand == "*"){
        // multiplication
        result = operator_bottom * operator_top;

    } else if (operand == "/"){
        // division
        if(operator_top == 0){
            throw std::invalid_argument( "Division by zero!" );
        }
        result = operator_bottom / operator_top;

    } else if (operand == "**") {
        // exponent
        if(operator_bottom == 0 && operator_top == 0){
            throw std::invalid_argument( "Exponentiation of zero!" );
        }
        result = pow(operator_bottom, operator_top);

    } else if (operand == "<"){
        // ceiling
        numStack.push_back(operator_top);
        result = ceil(operator_bottom);

    } else if (operand == ">"){
        // floor
        numStack.push_back(operator_top);
        result = floor(operator_bottom);

    } else {
        // invalid operand
        throw std::invalid_argument( "Invalid operand!" );
    }
    numStack.push_back(result);
    return 0;
}


// implement reverse polish notation using a stack
double rpn(string *strs, int strs_length) {

    double result = 0;
    list<double> numberStack;

    for(int i = 0; i < strs_length; i++){
        if(!is_operator(strs[i])){ // add to stack
            // add to stack
            cout << stod(strs[i]) << ' ';
            cout << "not operator" << '\n';
            numberStack.push_back(stod(strs[i]));

        } else if(is_operator(strs[i]))  {
            // perform operation on stack
            cout << strs[i] << " ";
            cout << "operator" << '\n';
            double success = perform_operation(strs[i], numberStack);
        } else {
            // error
            throw std::invalid_argument( "Invalid rph element!" );
        }

        for (auto const &r: numberStack) {
            std::cout << r << " ";
        }
        cout << endl;
    }


    return result;
}


struct Node {
    string data;
    struct Node *left, *right;

    Node(string d, Node *l, Node *r){
        data = std::move(d);
        left = l;
        right = r;
    }

    Node(){
        data = " ";
        left = nullptr;
        right = nullptr;
    }

    bool is_leaf_node() const {
        if (left == nullptr && right == nullptr){
            return true;
        } else {
            return false;
        }
    }
};


void print_ast(Node* root, int level){
    if (root != nullptr) {

        if(!root->is_leaf_node()){
            cout<<"(";
        }

        cout<<root->data<<" ";
        print_ast(root->left, level++);
        print_ast(root->right, level++);

        if(!root->is_leaf_node()){
            cout<<")";
        }
    }
}


void ast(string *strs, int strs_length){
    list<Node*> stack;

    for(int i = 0; i < strs_length; i++){
        if (is_operator(strs[i])){
            // do thing
            Node *rightElem = stack.back();
            stack.pop_back();

            Node *leftElem = stack.back();
            stack.pop_back();

            Node *newNode;
            newNode = new Node(strs[i], leftElem, rightElem);

            stack.push_back(newNode);
        } else {
            // do other thing
            Node *newNode;
            newNode = new Node();

            newNode->data = strs[i];
            bool is_leaf = newNode->is_leaf_node();

            stack.push_back(newNode);
        }
    }

    print_ast(stack.front(), 0);
}