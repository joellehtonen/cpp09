#pragma once
#include "PmergeMe.hpp"
#include <vector>
#include <list>

void swapValues(PmergeMe one, PmergeMe two);
void sortVector(std::vector<PmergeMe>& container);

template <typename T>
void giveNewRanks(T container, int pairValue)
{
    for (size_t i = 0; i < container.size(); i++)
    {
        container.at(i).setRank(i % pairValue + 1);
    }
};

template <typename T>
void uncheckAll(T container)
{
    for (size_t i = 0; i < container.size(); i++)
    {
        container.at(i).setChecked(false);
    }
};

template <typename T>
void printContainerContents(const T& container)
{
    for (auto it : container)
        std::cout << it.getValue() << " ";
    // for (size_t  i = 0; i < container.size(); i++)
    //     std::cout << container.at(i).getValue() << " ";
    std::cout << std::endl;
};