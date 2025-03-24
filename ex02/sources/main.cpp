#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
// 11 2 17 0 16 8 6 15 10 3 21 1 18 9 14 19 12 5 4 20 13 7

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
        checkResultOrder(vector);
        std::cout << "\n\n\n";

        // std::cout << "sorting list...\n";
        // auto startList = std::chrono::steady_clock::now();
        // resetComparisons();
        // sortList(list);
        // auto stopList = std::chrono::steady_clock::now();
        // checkResultOrder(list);

        std::cout << "AFTER: ";
        printContainerContents(vector);

        auto durationVector = std::chrono::duration<double, std::milli>(stopVector - startVector);
        //auto durationList = std::chrono::duration<double, std::milli>(stopList - startList);
        std::cout << "Time to sort " << vector.size() << " elements with vector: " << durationVector.count() << " milliseconds" << std::endl;
        //std::cout << "Time to sort " << list.size() << " elements with list: " << durationList.count() << " milliseconds" << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error. " << e.what() << "\n";
    }
}
