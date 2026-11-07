#include <iostream>
#include <string>
#include <stack>
#include <cassert>

bool isBalanced(const std::string &s)
{
    std::stack<char> open;

    //loops through the string
    for (char c : s){
        //checks for open brackets
        if (c == '(' || c == '[' || c == '{'){
            //adds the open bracket to the stack
            open.push(c);
            //checks for closing brackets
        } else if (c == ')' || c == ']' || c == '}'){
            //checks if the stack is empty, which means there is no matching open bracket
            if (open.empty()){
                return false;
            }
            char last = open.top();
            open.pop();
            //checks if the last open bracket matches the current closing bracket
            if ((c == ')' && last != '(') ||
                (c == ']' && last != '[') ||
                (c == '}' && last != '{')){
                return false;
            }
        }
    }
    //checks if there are any unmatched open brackets left in the stack
    return open.empty();
}

int main()
{
    // Simple cases
    assert(isBalanced("()") == true);
    assert(isBalanced("[]") == true);
    assert(isBalanced("{}") == true);
    assert(isBalanced("([]{})") == true);
    assert(isBalanced("{[()()]}") == true);

    // Wrong type or order
    assert(isBalanced("(]") == false);
    assert(isBalanced("([)]") == false);

    // Too many openers or closers
    assert(isBalanced("(()") == false);
    assert(isBalanced("())") == false);
    assert(isBalanced(")(") == false);
    assert(isBalanced("]") == false);

    // Edge cases
    assert(isBalanced("") == true);
    assert(isBalanced("hello") == true);
    assert(isBalanced("if (x[0] == 1) { y(); }") == true);

    std::cout << "All tests passed!\n";
    return 0;
}