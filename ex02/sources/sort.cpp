#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

void sortVector(std::vector<PmergeMe>& container)
{
    //comparing/swapping each number (1), then pair (2), and then pair of pairs (4), etc, 8, 16, 32... 
    for (size_t pairValue = 1; pairValue < container.size() / 2; pairValue *= 2)
    {
        for (size_t i = 0; i < container.size(); i += pairValue)
        {
            if (i + pairValue > container.size())
                break ;
            if (container.at(i).getChecked() == true)
                continue ;
            if (container.at(i).getValue() > container.at(i + pairValue).getValue())
            {
                for (i = 0; i < pairValue; i++)
                {
                    swapValues(container.at(i), container.at(i + pairValue));
                    container.at(i).setChecked(true);
                    container.at(i + pairValue).setChecked(true);
                }
            }
        }
        giveNewRanks(container, pairValue);
        uncheckAll(container);
    }
};