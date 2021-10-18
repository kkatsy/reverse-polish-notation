/*
 * Name: Katya Katsy
 * Email: kkatsy@ucdavis.edu
*/

#include "rpn.h"
#include <iostream>

int main() {
    // program input
    string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"};
    int test_length = sizeof(test)/sizeof(test[0]);

    // calculate result of reverse polish notation
    double result = rpn(test, test_length);
    cout << "Result: " << result << endl << endl;

    // print out the visualization
    cout << "Abstract Syntax Tree:" << endl;
    ast(test, test_length);
}