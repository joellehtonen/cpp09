#include "RPN.hpp"

int main(int ac, char** av)
{
    if (ac == 2)
    {
        RPN* calculator = new RPN();
        try {
            calculator->calculate(av[1]);
        }
        catch (std::exception& e)
        {
            std::cerr << "Error. " << e.what() << std::endl;
        }
        delete calculator;
    }
    else
        std::cout << "Only one argument accepted" << std::endl;
}