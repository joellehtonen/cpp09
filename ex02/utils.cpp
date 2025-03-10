#include "PmergeMe.hpp"

void swapValues(PmergeMe one, PmergeMe two)
{
    if (one.getRank() == two.getRank())
    {
        PmergeMe temp;
        temp.setValue(one.getValue());
        one.setValue(two.getValue());
        two.setValue(temp.getValue());
    }
};

template <typename T>
void giveRanks(T container, int pairValue)
{
    for (int i = 0; i < container.size(); i++)
    {

    }
};