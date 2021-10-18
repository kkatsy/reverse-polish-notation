#include "rpn.h"
#include <iostream>

int main() {
    string test[] = {"2", "12", "6", "-", "/", "5", "3", "+", "*"};
    int test_length = sizeof(test)/sizeof(test[0]);
    double bad = 0;
    double result = rpn(test, test_length);
    ast(test, test_length);
}