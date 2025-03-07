#include "RPN.hpp"

RPN::RPN() { };
RPN::~RPN() { };
RPN::RPN(const RPN& copy) : calculator(copy.calculator) { };
RPN& RPN::operator=(const RPN& copy){
    if (this != &copy)
    {
        this->calculator = copy.calculator;
    }
    return *this;
};

void RPN::calculate(std::string originalArgument)
{
    std::stringstream arguments(originalArgument);
    std::string part;
    bool operationDone = false;

    if (originalArgument.find_first_not_of("0123456789 +-/*") != std::string::npos)
        throw std::runtime_error("Invalid characters in the argument");
    while(arguments >> part)
    {
        if (part.find_first_of("0123456789") != std::string::npos)
        {
            int number = stoi(part);
            calculator.push(number);
        }
        else if (calculator.size() >= 2)
        {
            operationDone = true;
            int first = calculator.top();
            calculator.pop();
            //std::cout << "first: " << first << std::endl; 
            int second = calculator.top();
            calculator.pop();
            //std::cout << "second: " << second << std::endl; 
            //std::cout << "operator: " << part << std::endl;
            int result = arithmetic(second, first, part);
            //std::cout << "result: " << result << std::endl;
            calculator.push(result);
        }
        else
            throw std::runtime_error("Calculator needs at least 2 numbers before an operator to function");
    }
    if (operationDone == true)
    {
        int finalResult = calculator.top();
        std::cout << finalResult << std::endl;
    }
    else
    {
        throw std::runtime_error("At least one mathematical operator is needed");
    }
}

int RPN::arithmetic(int& first, int& second, std::string& part) {
    if (part == "+")
        return (first + second);
    if (part == "-")
        return (first - second);
    if (part == "/")
        return (first / second);
    if (part == "*")
        return (first * second);
    return (0);
};