#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

void checkInput(int ac, char** av)
{
    if (checkDigits(ac, av) == false)
        throw std::runtime_error("Only digits accepted");
    if (checkDuplicates(ac, av) == false)
        throw std::runtime_error("No duplicates allowed");
    if (checkOrder(ac, av) == false)
        throw std::runtime_error("Array already in order");
}

int main (int ac, char** av)
{
    std::vector<PmergeMe>   vctr;
    std::list<PmergeMe>     list;
    try { 
        checkInput(ac, av); 
    }
    catch (std::exception& e) {
        std::cerr << "Error. " << e.what() << "\n";
    }
    for (int i = 1; i < ac; i++)
    {
        vctr.push_back(PmergeMe(av[i]));
        list.push_back(PmergeMe(av[i]));
    }
    std::cout << "BEFORE: ";
    printContainerContents(vctr);

    std::cout << "SORTING VECTOR\n";
    try {
        sortVector(vctr);
    }
    catch (std::exception& e) {
        std::cerr << "Error. " << e.what() << "\n";
    }
    //stop timer
    //print timer
    printContainerContents(vctr);
    checkResultOrder(vctr);

    std::cout << "SORTING LIST\n";
    try {
        sortList(list);
    }
    catch (std::exception& e) {
        std::cerr << "Error. " << e.what() << "\n";
    }
    printContainerContents(vctr);
    checkResultOrder(vctr);
    //stop timer
    //print timer
}