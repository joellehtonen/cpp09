#pragma once
#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <climits>

class RPN {
    private:
        std::stack<double> calculator;
        double arithmetic(double& first, double& second, std::string& operation);
    public:
        RPN();
        ~RPN();
        RPN(const RPN& copy);
        RPN& operator=(const RPN& copy);

        void calculate(std::string argument);

};