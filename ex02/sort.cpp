#include "PmergeMe.hpp"
#include "utils.cpp"

template <typename T>
void sort(T container)
{
    //comparing/swapping each number
    for (int i = 0; i < container.size(); i++)
    {
        if (i + 1 > container.size())
            break ;
        if (container.at(i).getSorted() == true)
            continue ;
        if (container.at(i).getValue() > container.at(i + 1).getValue())
        {
            swapValues(container.at(i), container.at(i + 1));
            container.at(i).setSorted(true);
            container.at(i + 1).setSorted(true);
        }
    }

    //comparing/swapping each pair and pair of pairs, etc. 
    for (int pairValue = 2; pairValue < container.size() / 2; pairValue * 2)
    {
        giveRanks(container, pairValue);
        
        //something
    }
};