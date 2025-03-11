#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

int main (int ac, char** av)
{
    std::vector<PmergeMe>   vctr;
    std::list<PmergeMe>     lst;
    //check if input only valid digits
    //check for duplicates
    //start timer
    for (int i = 1; i < ac; i++)
    {
        vctr.push_back(PmergeMe(av[i]));
    }
    printContainerContents(vctr);
    try {
        sortVector(vctr);
    }
    catch (std::exception& e) {
        std::cerr << "Error. " << e.what() << "\n";
    }
    printContainerContents(vctr);
    //stop timer
    //print timer
    //same again with the other container
};

