#ifndef MY_INFIX_CALCULATOR
#define MY_INFIX_CALCULATOR

#include "myStack_c699k482.h"
#include <string>
#include <vector>

class myInfixCalculator {
    public:
    myInfixCalculator() {};
    ~myInfixCalculator() {};

    void tokenize(const std::string &s, std::vector<std::string> &tokens) {
        int vector_index = 0;
        int space_count = 0;
        tokens.reserve(s.length());
        tokens.resize(s.length());

        for(int i = 0; i < s.length(); i++) {
            std::string str(1, s[i]);
            
            if(isNumeric(str)) {  // Append numbers
                tokens[vector_index] += str;
                if(i != s.length() - 1) {
                    std::string next(1, s[i+1]);
                    if(!isNumeric(next)) {
                        vector_index++;
                    }
                }
            } else if (isOperator(str)) { // Add operators in new index
                tokens[vector_index] += str;
                if(i != s.length() - 1) {
                    vector_index++;
                }
            } else {
                space_count++;
            }
        }

        tokens.resize(vector_index + 1);
    }

    bool isOperator(std::string &s) {
        return (s == "(" || s == ")" || s == "*" || s == "/" || s == "+" || s == "-");
    }

    bool isNumeric(std::string &s) {
        return (!isOperator(s) && s != " ");
    }

    int assignPriority(std::string &str) {
        if(str == ")") {
            return 3;
        } else if(str == "*" || str == "/") {
            return 2;
        } else if (str == "+" || str == "-"){ 
            return 1;
        } else { // str == "("
            return 0;
        }
    }

    bool isHigherPriority(std::string &a_str, std::string &b_str) { // is A >= B
        int a, b;
        a = assignPriority(a_str);
        b = assignPriority(b_str);
        return a > b;
    }

    std::string infixToPostfix(const std::string &s) {
        std::vector<std::string> tokens;
        tokenize(s, tokens);
        myStack<std::string> stack(tokens.size());
        std::string output;

        for(int i = 0; i < tokens.size(); i++) {
            if(isNumeric(tokens[i])) {
                output += tokens[i] += " ";
            } else { // isOperator
                if (tokens[i] == "(") {
                    stack.push(tokens[i]);
                } else if (tokens[i] == ")") {
                    while (stack.top() != "(") {
                        output += stack.top() + " ";
                        stack.pop();
                    }
                    stack.pop(); // pop "("
                } else if (stack.empty()) {
                    stack.push(tokens[i]);
                } else if (isHigherPriority(tokens[i], stack.top())) {
                    stack.push(tokens[i]);
                } else {
                    while (!stack.empty()) {
                        if (!isHigherPriority(tokens[i], stack.top())) {
                            output += stack.top() + " ";
                            stack.pop();
                        } else {
                            break;
                        }
                    }
                    stack.push(tokens[i]);
                }
            }
            std::string stack_str;
            myStack<std::string> stack_copy = stack;
            while(!stack_copy.empty()) {
                stack_str += stack_copy.top();
                stack_copy.pop();
            }
        }
        while (!stack.empty()) {
            output += stack.top() += " ";
            stack.pop();
        }

        return output;
    }

    double calculatePostfix(const std::string & s) {
        std::vector<std::string> tokens;
        tokenize(s, tokens);
        myStack<double> stack(tokens.size());
        
        double result = 0.0;

        for (int i = 0; i < tokens.size() - 1; i++) {
            if(isNumeric(tokens[i])) {
                stack.push(stod(tokens[i]));
            } else {
                result = stack.top();
                stack.pop();
                if (tokens[i] == "+") {         // operator
                    result += stack.top();
                } else if (tokens[i] == "-") {  // operator
                    result = stack.top() - result;
                } else if (tokens[i] == "*") {  // operator
                    result *= stack.top();
                } else if (tokens[i] == "/") {  // operator
                    result = stack.top()/result;
                }
                stack.pop();
                stack.push(result);
            }
            std::string stack_str;
            myStack<double> stack_copy = stack;
            while(!stack_copy.empty()) {
                stack_str += std::to_string(stack_copy.top()) + " ";
                stack_copy.pop();
            }
        }
        return stack.top();
    }
};
#endif //MY_INFIX_CALCULATOR