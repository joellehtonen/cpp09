#include "../includes/utils.hpp"

template <typename T>
void giveNewRanks(T& container, int pairValue)
{
    int i = 0;
    for (auto it = container.begin(); it != container.end(); ++it, ++i)
    {
        it->setRank(i % pairValue + 1);
		std::cout << std::left << "number: " << std::setw(8) << it->getValue() << " rank: " << std::setw(16) << it->getRank() << std::endl;
    }
};

template <typename T>
void updateGroups(T& container, int pairValue)
{
    int group = 0;
    int counter = 0;
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        it->addGroup(group);
        counter++;
        if (counter == pairValue)
        {
            group++;
            counter = 0;
        }
	}
};

template <typename T>
void printGroups(const T& container)
{
    std::cout << "GROUPS: \n";
    for (auto it = container.begin(); it != container.end(); ++it)
    {
        std::cout << std::left << std::setw(16) << (std::to_string(it->getValue()) + " --> ");
        std::vector<int> printThis = it->getGroup();
        for (const int it : printThis)
            std::cout << std::setw(8) << it << " ";
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
        auto next = it;
        next++;
        if (next == container.end())
            break ;
        if (it->getValue() > next->getValue())
        {
            std::cout << "The container is NOT sorted\n";
            std::cout << it->getValue() << "is bigger than " << next->getValue();
            return false;
        }
    }
    std::cout << "The container is sorted\n";
    return true ;
};