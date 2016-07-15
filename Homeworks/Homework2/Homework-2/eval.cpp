/** @file: eval.cpp */

#include "Map.h"

#include <string>
#include <cassert>
#include <cctype>
#include <stack>
#include <iostream>
using namespace std;

int evaluate(string infix, const Map& values, string& postfix, int& result);
// Evaluates an integer arithmetic expression
// Precondition: infix is an infix integer arithmetic
//   expression consisting of single lower case letter operands,
//   parentheses, and the operators +, -, *, /, with embedded blanks
//   allowed for readability.
// Postcondition: If infix is a syntactically valid infix integer
//   expression whose only operands are single lower case letters
//   (whether or not they appear in the values map), then postfix is
//   set to the postfix form of the expression; otherwise postfix may
//   or may not be changed, result is unchanged, and the function
//   returns 1.  If infix is syntactically valid but contains at
//   least one lower case letter operand that does not appear in the
//   values map, then result is unchanged and the function returns 2.
//   If infix is syntactically valid and all its lower case operand
//   letters appear in the values map, then if evaluating the
//   expression (using for each letter in the expression the value in
//   the map that corresponds to it) attempts to divide by zero, then
//   result is unchanged and the function returns 3; otherwise,
//   result is set to the value of the expression and the function
//   returns 0.


/** Takes an infix expression and gets its postfix expression
    @pre: infix is an infix expression and postfix is a string to copy the postfix into.
    @param: infix: The string to get the postfix expression of.
    @param: postfix: The string to put the postfix expression into.
    @post: If succesful, postfix is changed to the postfix expression of infix. Otherwise
        postfix is unchanged.
    @return: True if infix is a valid infix expression. Otherwise returns false. */
bool toPostFix(const string& infix, string& postfix);


/** Takes in an infix expression and checks if it is syntactically valid
    @pre: infix is an infix expression.
    @param: infix: The string to check if it is a valid infix expression.
    @return: True if infix is a valid expression (i.e., there are only '+', '-', '/', '*',
        '(', ')', ' ', or single lowercase letters in the expression; there is at least 1
        single lowercase letter; the number of operators is equal to the number of 
        letters - 1; and there is a '(' for each and every ')'. Otherwise, returns false */
bool isSyntacticallyValid(const string& infix);


/** Takes in a character and returns true if it is a valid operator
    @param: ch: The character to check if it is an operator.
    @return: True if the character is a '-', '+', '*', or '/'. Otherwise
        returns false. */
bool isOperator(const char& ch);


/** Returns the precedence of an operator
    @param: ch: The character to get the precedence of
    @return: 1 if the the character is either a '-' or '+'.
        2 if the character is a '/' or '*'. 0 if the character is not
        an operator. */
int precedence(const char& ch);


int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    // if the infix expression is invalid, return 1
    if(!isSyntacticallyValid(infix))
        return 1;
    
    stack<int> S;
    
    toPostFix(infix, postfix); // Because it is valid, we can now make 'postfix' the postfix expression
    
    // Go through the postfix expression...
    for (int i = 0; i < postfix.size(); i++)
    {
        // if a character is an operand that is NOT in the map of values...
        if(isalpha(postfix[i]) && !values.contains(postfix[i]))
            // return 2 and stop all other operations.
            return 2;
        
        // if the character is a valid operand...
        if(isalpha(postfix[i]))
        {
            // get its mapped valud and push it onto the stack.
            int temp;
            values.get(postfix[i], temp);
            S.push(temp);
            
        } // end if
        
        // if the character is an operator...
        else if(isOperator(postfix[i]))
        {
            // get the top 2 operands from the stack.
            int num1, num2;
            num2 = S.top();
            S.pop();
            num1 = S.top();
            S.pop();
            
            // perform the operation on the two operands.
            int numToAdd;
            switch(postfix[i])
            {
                case '/':
                    if (num2 == 0) // if divide by 0, return 3.
                        return 3;
                    numToAdd = num1 / num2;
                    break;
                case '*':
                    numToAdd = num1 * num2;
                    break;
                case '+':
                    numToAdd = num1 + num2;
                    break;
                case '-':
                    numToAdd = num1 - num2;
                    break;
                default:
                    break;
                    
            } // end switch
            
            // push the result onto the stack.
            S.push(numToAdd);
        
        } // end else if
        
    } // end for
    
    // The last integer on the stack is the result of the entire expression.
    result = S.top();
    return 0;
    
} // end evaluate


bool toPostFix(const string& infix, string& postfix)
{
    // if the expression is invalid, there is nothing to do.
    if (!isSyntacticallyValid(infix))
        return false;
    
    postfix = "";
    stack<char> operatorStack;
    // go through the infix expression...
    for (int i = 0; i < infix.size(); i++)
    {
        // if the character is an operand...
        if(isalpha(infix[i]))
            // append it to the infix expresion.
            postfix += infix[i];
        
        // if the character is an open brace...
        else if(infix[i] == '(')
            // push it onto the stack.
            operatorStack.push(infix[i]);
        
        // if the character is an operator...
        else if (isOperator(infix[i]))
        {
            
            //  go through the stack until it is empty or you hit an open brace, and if the
            //  precedence of the operand on the top of the stack is higher than the precedence of
            //  the current operator, pop that operator and append it to the postfix expression.
            //  When there are no more operators with a higher precedence, push the current
            //  operator onto the stack.
            
            while (!operatorStack.empty() && operatorStack.top() != '(' && precedence(infix[i]) <= precedence(operatorStack.top()))
            {
                postfix += operatorStack.top();
                operatorStack.pop();
                
            } // end while
            
            operatorStack.push(infix[i]);
            
        } // end else if
        
        // if the character is a close brace...
        else if(infix[i] == ')')
        {
            // append all operators on the stack until you hit an open brace.
            while (operatorStack.top() != '(')
            {
                postfix += operatorStack.top();
                operatorStack.pop();
                
            } // end while
            
            operatorStack.pop();
            
        } // end else if
        
    } // end for
    
    // Now just append the rest of the stack to the postfix expression.
    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
        
    } // end while
    
    return true;
    
} // end toPostFix


bool isSyntacticallyValid(const string& infix)
{
    // Keep a count of operators and operands
    int operatorCount = 0;
    int operandCount = 0;
    stack<char> paranStack;
    
    // Go through the infix expression...
    for (int i = 0; i < infix.size(); i++)
    {
        // if the character is a open brace...
        if (infix[i] == '(')
            // push it on the stack.
            paranStack.push(infix[i]);
        
        // if it is a close brace...
        else if (infix[i] == ')')
        {
            // check to see if there is an open brace on the stack.
            if(paranStack.empty())
                return false;
            else if(paranStack.top() != '(')
                return false;
            paranStack.pop();
            
        } // end if
        
        // if it is a lowercase letter...
        else if (isalpha(infix[i]) && islower(infix[i]))
            // increment the operand count.
            operandCount++;
        
        // if it is an operator...
        else if (isOperator(infix[i]))
            // increment the operator count.
            operatorCount++;
        
        // otherwise, return false (if it is not a space)
        else if (infix[i] != ' ')
            return false;
        
    } // end for
    
    
    //  At this point, the expression has all the possible characters to make it a valid expression, however, it might still not be a valid expression.
    
    //  if there are no operands, there is nothing to evaluate, and therefore no valid expression.
    if (operandCount == 0)
        return false;
    
    //  if there are more operators than operands, then the expression is inconclusive.
    if (operandCount != operatorCount+1)
        return false;
    
    //  if there are still paranthesis in the stack, then there was not a closing brace for an open brace
    if (!paranStack.empty())
        return false;
    
    return true;
    
} // end isValidInfix


bool isOperator(const char& ch)
{
    if (ch == '*' || ch == '+' || ch == '-' || ch == '/')
        return true;
    return false;
    
} // end isOperator


int precedence(const char& ch)
{
    switch(ch)
    {
        case '-':
            return 1;
        case '+':
            return 1;
        case '*':
            return 2;
        case '/':
            return 2;
        default:
            return 0;
    } // end switch
    
} // end precedence

