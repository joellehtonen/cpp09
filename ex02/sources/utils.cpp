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
        if (i + 1 >= container.size())
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

void insertion(std::vector<PmergeMe>& container, size_t& pairValue)
{
    std::vector<PmergeMe> pend;

    for (; pairValue > 2; pairValue /= 2)
    {
        std::cout << "pair value = " << pairValue << std::endl;
        size_t comparisonIndex = pairValue * 3 - 1;
        if (comparisonIndex > container.size())
            continue ;
        size_t pendIndex = 2;
        while (comparisonIndex + pairValue < container.size())
        {
            std::cout << "comparing " << container.at(comparisonIndex).getValue();
            std::cout << " with " << container.at(comparisonIndex + pairValue).getValue() << std::endl;
            if (container.at(comparisonIndex).getValue() < container.at(comparisonIndex + pairValue).getValue())
                moveToPend(container, pend, pairValue, comparisonIndex - pairValue + 1, pendIndex);
            else
                moveToPend(container, pend, pairValue, comparisonIndex + 1, pendIndex);
            comparisonIndex += pairValue;
            pendIndex++;
        }
        giveIndexes(container, pairValue);
        insertBackToMain(container, pend, pairValue);
        printContainerContents(container);
    }
};

void moveToPend(std::vector<PmergeMe>& container, std::vector<PmergeMe>& pend, const size_t& pairValue, const size_t& moveIndex, const size_t& pendIndex)
{
    auto it = container.begin();
    std::advance(it, moveIndex);
    for (size_t i = 0; i < pairValue; i++)
    {
        container.at(moveIndex).setIndex(pendIndex);
        container.at(moveIndex).setLetter('B');
        pend.push_back(container.at(moveIndex));
        it = container.erase(it);
    }
    std::cout << "in the pend now: ";
    printContainerContents(pend);
    std::cout << "in the main now: ";
    printContainerContents(container);
    std::cout << std::endl;
};

void giveIndexes(std::vector<PmergeMe>& container, const size_t& pairValue)
{
    //special case for the first element in the main
    container.at(0).setIndex(1);
    container.at(0).setLetter('B');
    //give indexes to other elements left in the container (the main)
    int index = 1;
    for (size_t i = 1; i < container.size(); i++)
    {
        for (size_t j = 0; j < pairValue; j++)
        {
            container.at(i).setIndex(index);
            container.at(i).setLetter('A');
        }
        index++;
    }
};

void insertBackToMain(std::vector<PmergeMe>& container, std::vector<PmergeMe>& pend, const size_t& pairValue)
{
    std::vector<int> jacobsthal = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461};

    for (size_t jacobIndex = 1; pend.empty() == false; jacobIndex++)
    {
        const_iterator elementCompPos = findNextPosition(pend, jacobsthal.at(jacobIndex), pairValue);
        const_iterator elementMovePos = elementCompPos - pairValue - 1;
        const_iterator lastPos = findLastPosition(pend, jacobsthal.at(jacobIndex - 1) + 1);
        const_iterator insertPos = findTargetPosition(container, *elementCompPos, pairValue);
        std::cout << "TARGET INDEX = " << elementCompPos->getIndex() << std::endl; //TEST
        std::cout << "TARGET VALUE = " << elementCompPos->getValue() << std::endl; //TEST
        std::cout << "LAST INDEX = " << lastPos->getIndex() << std::endl; //TEST
        std::cout << "FIRST TO MOVE = " << elementMovePos->getValue() << std::endl; //TEST
        for (; elementCompPos >= lastPos; elementCompPos--)
        {
            for (size_t i = 0; i < pairValue; i++)
            {
                std::cout << "inserting " << elementMovePos->getValue() << " into index " << insertPos->getIndex() << std::endl;
                container.insert(insertPos, *elementMovePos);
                pend.erase(elementMovePos);
                insertPos++;
            }
            //std::cout << "one pair done\n";
        }
    }
};

const_iterator findNextPosition(std::vector<PmergeMe>& pend, const int& jacobNumber, const size_t& pairValue)
{
    std::cout << "pair value = " << pairValue << std::endl;
    for (auto it = pend.begin(); it != pend.end(); it++)
    {
        // std::cout << "index of " << it->getValue() << " is " << it->getIndex() << std::endl;
        if (it->getIndex() == jacobNumber)
            return it;
    }
    return pend.end() - 1;
};

const_iterator findLastPosition(std::vector<PmergeMe>& pend, const int& jacobNumber)
{
    for (auto it = pend.begin(); it != pend.end(); it++)
    {
        if (it->getIndex() == jacobNumber)
            return it;
    }
    return pend.begin();
};

const_iterator findTargetPosition(std::vector<PmergeMe>& container, const PmergeMe& element, const size_t& pairValue)
{
    for (auto it = container.begin() + pairValue - 1; it != container.end(); it += pairValue)
    {
        std::cout << "comparing " << element.getValue() << " with " << it->getValue() << std::endl;
        if (element.getValue() < it->getValue())
            return it;
        if (element.getIndex() <= it->getIndex() && it->getLetter() == 'A')
            return it;
    }
    return container.begin();
};