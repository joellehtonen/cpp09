#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

// comparing/swapping each number (1), then pair (2), and then pair of pairs (4), etc, 8, 16, 32... 
void sortVector(std::vector<PmergeMe>& container)
{
    firstComparison(container);
    size_t pairValue = formPairs(container);
    std::cout << "pair = " << pairValue << std::endl;
    printGroups(container); //TEST
    insertion(container, pairValue);
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

size_t formPairs(std::vector<PmergeMe>& container)
{
    printContainerContents(container); //TEST
    std::cout << "NEXT ROUND\n"; //TEST
    size_t pairValue = 2;
    for (; pairValue <= container.size() / 2; pairValue *= 2)
    {
        //giveNewRanks(container, pairValue);
        for (size_t i = 0; i < container.size(); i += pairValue * 2)
        {
            if (i + pairValue * 2 > container.size())
                break ;
            comparePairs(container, i, pairValue);
        }
        updateGroups(container, pairValue);
        std::cout << "NEXT ROUND\n"; //TEST
        printContainerContents(container); //TEST
    }
    return pairValue / 2;
};

void comparePairs(std::vector<PmergeMe>& container, size_t& i, size_t& pairValue)
{
    size_t firstPairIndex = i + pairValue - 1;
    size_t secondPairIndex = i + pairValue * 2 - 1;

    std::cout << "comparing " << container.at(firstPairIndex).getValue() << " with " << container.at(secondPairIndex).getValue() << "\n";
    if (container.at(firstPairIndex).getValue() > container.at(secondPairIndex).getValue())
    {
        std::cout << "swapping\n";
        for (size_t j = 0; j < pairValue; j++)
            std::swap(container.at(i + j), container.at(i + j + pairValue));
    }
};

void insertion(std::vector<PmergeMe>& container, size_t pairValue)
{
    std::vector<PmergeMe> pend;

    for (; pairValue > 2; pairValue /= 2)
    {
        size_t comparisonIndex = pairValue * 3 - 1;
        if (comparisonIndex > container.size())
            continue ;
        while (comparisonIndex < container.size())  //double check if this is valid
        {
            if (container.at(comparisonIndex).getValue() < container.at(comparisonIndex + pairValue).getValue())
                moveToPend(container, pend, pairValue, comparisonIndex - pairValue);
            else
                moveToPend(container, pend, pairValue, comparisonIndex + 1);
        }
        giveIndexes(container, pend, pairValue);
        insertToMain


    }
};

void moveToPend(std::vector<PmergeMe>& container, std::vector<PmergeMe> pend, size_t pairValue, size_t moveIndex)
{
    auto it = container.begin();
    std::advance(it, moveIndex);
    for (size_t i = 0; i < pairValue; i++)
    {
        pend.push_back(container.at(moveIndex));
        it = container.erase(it);
    }
};

void giveIndexes(std::vector<PmergeMe>& container, std::vector<PmergeMe>& pend, size_t pairValue)
{
    //give indexes to elements left in the container (the main)
    int index = 0;
    for (int i = 0; i < container.size(); i++)
    {
        for (int j = 0; j < pairValue; j++)
        {
            container.at(i).setIndex(index);
        }
        index++;
    }
    //give indexes to elements in the pend
    index = 2;
    for (int i = 0; i < pend.size(); i++)
    {
        for (int j = 0; j < pairValue; j++)
        {
            pend.at(i).setIndex(index);
        }
        index++;
    }
};

void insertToMain(std::vector<PmergeMe>& container, std::vector<PmergeMe> pend, size_t pairValue)
{
    std::vector<int> jacobsthal = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461};

    for (size_t jacobIndex = 1; pend.empty() == true; jacobIndex++)
    {
        size_t index = findNextIndex(pend, jacobsthal.at(jacobIndex));
        size_t lastIndex = jacobsthal.at(jacobIndex - 1) + 1;
        std::cout << "LAST INDEX = " << lastIndex << std::endl; //TEST
        for (; index >= lastIndex; index--)
        {
            auto it = pend.begin();
            std::advance(it, index);
            for (size_t i = 0; i < pairValue; i++)
            {
                pend.push_back(container.at(moveIndex));
                it = container.erase(it);
            }
        }
    }
};

size_t findNextIndex(std::vector<PmergeMe> pend, size_t jacobNumber)
{
    size_t index;
    size_t lastElement = pend.size() - 1;
    for (size_t i = 0; i < lastElement; i++)
    {
        index = pend.at(i).getIndex();
        if (index == jacobNumber)
            return index;
    }
    return lastElement;
}