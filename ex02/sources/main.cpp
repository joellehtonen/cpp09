#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`

void checkInput(int ac, char** av)
{
    if (ac < 2)
        throw std::runtime_error("Not enough arguments");
    if (checkDigits(ac, av) == false)
        throw std::runtime_error("Only non-negative integers accepted");
    if (checkDuplicates(ac, av) == false)
        throw std::runtime_error("No duplicates allowed");
    if (checkOrder(ac, av) == false)
        throw std::runtime_error("Array already in order");
}

int main (int ac, char** av)
{
    std::vector<PmergeMe>   vector;
    std::list<PmergeMe>     list;
    try { 
        checkInput(ac, av); 
        for (int i = 1; i < ac; i++)
        {
            vector.push_back(PmergeMe(av[i]));
            list.push_back(PmergeMe(av[i]));
        }
        std::cout << "BEFORE: ";
        printContainerContents(vector);
        std::cout << "sorting vector...\n";
        auto startVector = std::chrono::steady_clock::now();
        sortVector(vector);
        auto stopVector = std::chrono::steady_clock::now();
        //checkResultOrder(vctr);

        std::cout << "sorting list...\n";
        auto startList = std::chrono::steady_clock::now();
        sortList(list);
        auto stopList = std::chrono::steady_clock::now();
        //checkResultOrder(list);

        std::cout << "AFTER: ";
        printContainerContents(vector);

        std::chrono::duration<double> durationVector = std::chrono::duration_cast<std::chrono::milliseconds>(stopVector - startVector);
        std::chrono::duration<double> durationList = std::chrono::duration_cast<std::chrono::milliseconds>(stopList - startList);
        std::cout << "Time to sort " << vector.size() << " elements with vector: " << durationVector.count() << " seconds" << std::endl;
        std::cout << "Time to sort " << list.size() << " elements with list: " << durationList.count() << " seconds" << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error. " << e.what() << "\n";
    }
}