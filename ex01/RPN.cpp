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
            double number = stod(part);
            calculator.push(number);
        }
        else if (calculator.size() >= 2)
        {
            double first = calculator.top();
            calculator.pop();
            //std::cout << "first: " << first << std::endl; 
            double second = calculator.top();
            calculator.pop();
            //std::cout << "second: " << second << std::endl; 
            //std::cout << "operator: " << part << std::endl;
            double result = arithmetic(second, first, part);
            //std::cout << "result: " << result << std::endl;
            calculator.push(result);
            operationDone = true;
        }
        else
            throw std::runtime_error("Calculator needs at least 2 numbers before an operator to function");
    }
    if (operationDone == true)
    {
        double finalResult = calculator.top();
        calculator.pop();
        if (calculator.empty() == false)
            throw std::runtime_error("Invalid input");
        else if (finalResult > INT_MAX || finalResult < INT_MIN)
            throw std::runtime_error("Result overflows");
        else
        {
            int intResult = static_cast<int>(finalResult);
            std::cout << intResult << std::endl;
        }
    }
    else
    {
        throw std::runtime_error("At least one mathematical operator is needed");
    }
};

double RPN::arithmetic(double& first, double& second, std::string& part) {
    if (part == "+")
        return (first + second);
    if (part == "-")
        return (first - second);
    if (part == "/")
    {
        if (first == 0 || second == 0)
            throw std::runtime_error("Cannot divide by zero");
        return (first / second);
    }
    if (part == "*")
        return (first * second);
    return (0);
};