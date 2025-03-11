#include "../includes/utils.hpp"

//TODO REMAKE TO USE ITERATORS
template <typename T>
void giveNewRanks(T& container, int pairValue)
{
    for (size_t i = 0; i < container.size(); i++)
    {
        container.at(i).setRank(i % pairValue + 1);
		std::cout << "number " << container.at(i).getValue() << " has rank " << container.at(i).getRank() << "\n";
    }
};

template <typename T>
void printContainerContents(const T& container)
{
    for (auto it : container)
        std::cout << it.getValue() << " ";
    std::cout << std::endl;
};