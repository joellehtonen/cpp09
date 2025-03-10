#include "../includes/PmergeMe.hpp"

void swapValues(PmergeMe one, PmergeMe two)
{
    PmergeMe temp;
    temp.setValue(one.getValue());
    one.setValue(two.getValue());
    two.setValue(temp.getValue());
};