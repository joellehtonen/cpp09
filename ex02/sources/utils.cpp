#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

//TODO check all, not just those that have to be swapped
//TODO compare items that pairValue/end of the pair, not first values of each pair
//TODO maybe separate func for first comparisons

// comparing/swapping each number (1), then pair (2), and then pair of pairs (4), etc, 8, 16, 32... 
void sortVector(std::vector<PmergeMe>& container)
{
    firstComparison(container);
    printContainerContents(container); //TEST
    std::cout << "NEXT ROUND\n"; //TEST
    for (size_t pairValue = 2; pairValue <= container.size() / 2; pairValue *= 2)
    {
        //giveNewRanks(container, pairValue);
        for (size_t i = 0; i < container.size(); i += pairValue)
        {
            std::cout << "i is " << i << "\n";
            if (i + pairValue + pairValue > container.size())
            {
                std::cout << "BREAK!\n";
                break ;
            }
            if (container.at(i).getChecked() == true)
            {
                continue ;
            }
            comparePairs(container, i, pairValue);
            //check all
        }
        uncheckAll(container);
        std::cout << "NEXT ROUND\n"; //TEST
        printContainerContents(container); //TEST
    }
};

void firstComparison(std::vector<PmergeMe>& container)
{
    for (size_t i = 0; i < container.size(); i += 2)
    {
        if (i + 1 > container.size())
            break ;
        std::cout << "comparing " << container.at(i).getValue() << " with " << container.at(i + 1).getValue() << "\n";
        if (container.at(i).getValue() > container.at(i + 1).getValue())
            std::swap(container.at(i), container.at(i + 1));
    }
};

void comparePairs(std::vector<PmergeMe>& container, size_t& i, size_t& pairValue)
{
    size_t firstPairIndex = i + pairValue - 1;
    size_t secondPairIndex = i + pairValue + pairValue - 1;
    std::cout << "comparing " << container.at(firstPairIndex).getValue() << " with " << container.at(secondPairIndex).getValue() << "\n";
    if (container.at(firstPairIndex).getValue() > container.at(secondPairIndex).getValue())
    {
        for (size_t j = 0; j <= pairValue; j++)
            std::swap(container.at(i + j), container.at(i + j + pairValue));
    }
    for (size_t k = 0; k <= pairValue; k++)
    {
        container.at(i + k).setChecked(true);
        container.at(i + k + pairValue).setChecked(true);
    }
};

// void swapValues(PmergeMe& one, PmergeMe& two)
// {
//     std::swap(one, two);
//     one.setChecked(true);
//     two.setChecked(true);
// };