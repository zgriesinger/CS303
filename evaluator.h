#include <string>
#include <stack>
#include <iostream>

using namespace std;

class Evaluator{

public:
    /*@param Input string that is an infix expression containing only integers and including the operands listed below
    Output: The function will output the proper value of the infix expression, if the infix expression involves the use 
    of boolean operators the answer will be output as a 1 or a 0 and the is_bool variable will be set to true. If not the answer
    will be simply returned (0 or 1 included) and is_bool should be false */
    
    int eval(string input);

private:
    /*This private variable container is going to be used to contain all of the operands from the input string. 
        Operands included are:              Precidence:         Type:
            !           logical not             8               Unary
            ++          prefix increment        8               Unary
            --          prefix decrement        8               Unary
            -           negative                8               Unary
            ^           power                   7               Unary
            *,/,%       arithmetic              6               Binary
            +,-         arithmetic              5               Binary
            >,>=,<,<=   comparison              4               Binary 
            =,!=        equality                3               Binary
            &&          logical and             2               Binary 
            //          logical or              1               Binary 
        And it needs to be able to throw an exception for the following errors: (more if they make sense)
            Two binary operators in a row
            Binary operator directly after a Unary operator
            Can't start with a Binary operator
        As operands are encountered they will be put onto the stack along with parentheses. Once we come accross closing
        parentheses we will need to pop off the proper operators and operands until we reach what was inside the smaller parentheses,
        use precedence and proceed to calculate accordingly. This will be done in the eval() function. */
        
    stack<int> operands;

    /*This private variable container is going to be used to contain all of the operators from the input string. 
        The assumption is that all given operators will be integers. Binary opeators and comparisons will return numbers (1 or 0) for 
        the solution and make the bool variable is_bool true. Then the answer will be converted to true or false at the end. The eval()
        function will have the job of popping the operators when needed.*/
    stack<string> operators;

    /* NOTE:I don't know if we need this or if there is a better way feel free to change this variable
        all it needs to do is be true if the answer we are going to print out is true and false if it is going to be a normal integer */
    bool is_bool;



};