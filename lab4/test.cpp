#include "myInfixCalculator_c699k482.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    //std::string s = "1+2*3+(4*5+6/7)*8+9";
    std::string s = "(2*17.74890948294636-4-16/3)*8+1.6349616238845335+(2+9*7)*26-(5*14.354850819984554-3-79)";
    //std::string s = "51 3+";
    //std::string p = "6 5 2 3 + 8 * + 3 + *";
    std::vector<std::string> tokens;
    myInfixCalculator calc;

    calc.tokenize(s, tokens);
    
    std::cout<<"Start: " << s << "\n";
    /*
    for(int i = 0; i < tokens.size(); i++) {
        std::cout << tokens[i] << "\n";
    }
    std::cout<<"End\n";
    */
    std::string p = calc.infixToPostfix(s);
    std::cout<<"Conversion:\t" << p << "\n";
    std::cout<<"Result:" << calc.calculatePostfix(p) << "\n";
    std::cout << "Actual: " << 1+2*3+(4*5+6/7)*8+9 << "\n";
}