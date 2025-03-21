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
        for (int i = 1; i < ac; i++)
        {
            vctr.push_back(PmergeMe(av[i]));
            list.push_back(PmergeMe(av[i]));
        }
        std::cout << "BEFORE: ";
        printContainerContents(vctr);

        // std::cout << "SORTING VECTOR\n";
        //start timer
        // sortVector(vctr);
        // printContainerContents(vctr);
        // checkResultOrder(vctr);
        //stop timer
        //print timer

        std::cout << "SORTING LIST\n";
        //start timer
        sortList(list);
        printContainerContents(list);
        checkResultOrder(list);
        //stop timer
        //print timer
    }
    catch (std::exception& e) {
        std::cerr << "Error. " << e.what() << "\n";
    }
}