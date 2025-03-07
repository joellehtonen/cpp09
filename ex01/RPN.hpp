#pragma once
#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>

class RPN {
    private:
        std::stack<int> calculator;
        int arithmetic(int& first, int& second, std::string& operation);
    public:
        RPN();
        ~RPN();
        RPN(const RPN& copy);
        RPN& operator=(const RPN& copy);

        void calculate(std::string argument);

};