#include "../includes/utils.hpp"

//TODO REMAKE TO USE ITERATORS
template <typename T>
void giveNewRanks(T& container, int pairValue)
{
    for (size_t i = 0; i < container.size(); i++)
    {
        container.at(i).setRank(i % pairValue + 1);
		std::cout << std::left << "number: " << std::setw(8) << container.at(i).getValue() << " rank: " << std::setw(16) << container.at(i).getRank() << std::endl;
    }
};

//TODO REMAKE TO USE ITERATORS
template <typename T>
void updateGroups(T& container, int pairValue)
{
    int group = 0;
    int counter = 0;
    for (size_t i = 0; i < container.size(); i++)
    {
        container.at(i).addGroup(group);
        counter++;
        if (counter == pairValue)
        {
            group++;
            counter = 0;
        }
	}
};

//TODO REMAKE TO USE ITERATORS
template <typename T>
void printGroups(const T& container)
{
    for (size_t i = 0; i < container.size(); i++)
    {
        std::cout << std::left << std::setw(8) << (std::to_string(container.at(i).getValue()) + " --> ");
        std::vector<int> printThis = container.at(i).getGroup();
        for (const int it : printThis)
            std::cout << std::setw(4) << it << " ";
        std::cout << std::endl;
	}
};

template <typename T>
void printIndexes(const T& main, const T& pend)
{
    std::cout << "indexes in the pend: ";
    for (auto it = pend.begin(); it != pend.end(); it++)
    {
        std::cout << it->getLetter() << it->getIndex() << " ";
    }
    std::cout << std::endl;
    std::cout << "indexes in the main: ";
    for (auto it = main.begin(); it != main.end(); it++)
    {
        std::cout << it->getLetter() << it->getIndex() << " ";
    }
    std::cout << std::endl;
};

template <typename T>
void printContainerContents(const T& container)
{
    for (auto it : container)
        std::cout << it.getValue() << " ";
    std::cout << std::endl;
};

template <typename T>
bool checkResultOrder(const T& container)
{
    for (auto it = container.begin(); it != container.end(); it++)
    {
        auto itNext = it;
        itNext++;
        if (itNext == container.end())
            break ;
        if (it->getValue() > itNext->getValue())
        {
            std::cout << "The container is NOT sorted\n";
            return false;
        }
    }
    std::cout << "The container is sorted\n";
    return true ;
};