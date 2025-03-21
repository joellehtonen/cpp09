#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

// comparing/swapping each number (1), then pair (2), and then pair of pairs (4), etc, 8, 16, 32... 
void sortVector(std::vector<PmergeMe>& container)
{
    firstComparison(container);
    size_t pairValue = formPairs(container);
    if (COMMENTS)
    {
        printGroups(container);
        printComparisonAmount();
    }
    insertion(container, pairValue);
    if (COMMENTS)
        printComparisonAmount();
};

void firstComparison(std::vector<PmergeMe>& container)
{
    for (size_t i = 0; i < container.size(); i += 2)
    {
        if (i + 1 >= container.size())
            break ;
        if (COMMENTS)
            std::cout << "comparing " << container.at(i).getValue() << " with " << container.at(i + 1).getValue() << "\n";
        if (compare(container.at(i), container.at(i + 1)))
        {
            std::swap(container.at(i), container.at(i + 1));
            if (COMMENTS)
                std::cout << "swap\n";
        }
    }
};

size_t formPairs(std::vector<PmergeMe>& container)
{
    if (COMMENTS)
        printContainerContents(container); //TEST
    size_t pairValue = 2;
    size_t maxSize = container.size() / 2;
    for (; pairValue <= maxSize; pairValue *= 2)
    {
        if (COMMENTS)
            giveNewRanks(container, pairValue);
        for (size_t i = 0; i < container.size(); i += pairValue * 2)
        {
            if (i + pairValue * 2 > container.size())
                break ;
            comparePairs(container, i, pairValue);
        }
        updateGroups(container, pairValue);
        if (COMMENTS)
            printContainerContents(container); //TEST
    }
    return pairValue / 2;
};

void comparePairs(std::vector<PmergeMe>& container, size_t& i, size_t& pairValue)
{
    size_t firstPairIndex = i + pairValue - 1;
    size_t secondPairIndex = i + pairValue * 2 - 1;

    if (COMMENTS)
        std::cout << "comparing " << container.at(firstPairIndex).getValue() << " with " << container.at(secondPairIndex).getValue() << "\n";
    if (compare(container.at(firstPairIndex), container.at(secondPairIndex)))
    {
        if (COMMENTS)
            std::cout << "swapping\n";
        for (size_t j = 0; j < pairValue; j++)
            std::swap(container.at(i + j), container.at(i + j + pairValue));
    }
};

void insertion(std::vector<PmergeMe>& main, size_t& pairValue)
{
    std::vector<PmergeMe> pend;

    for (; pairValue >= 1; pairValue /= 2)
    {
        if (COMMENTS)
            std::cout << "------- PAIR VALUE = " << pairValue << " -------" << std::endl;
        size_t comparisonIndex = pairValue * 3 - 1;
        if (comparisonIndex > main.size())
            continue ;
        size_t pendIndex = 2;
        while (comparisonIndex < main.size())
        {
            if (comparisonIndex + pairValue >= main.size())
            {
                if (COMMENTS)
                    std::cout << "no valid comps available, moving " << main.at(comparisonIndex).getValue() << " to pend\n";
                moveToPend(main, pend, pairValue, comparisonIndex - pairValue + 1, pendIndex);
            }
            else
            {
                if (COMMENTS)
                    std::cout << "comparing " << main.at(comparisonIndex).getValue() << " with " << main.at(comparisonIndex + pairValue).getValue() << std::endl;
                if (compare(main.at(comparisonIndex), main.at(comparisonIndex + pairValue)))
                    moveToPend(main, pend, pairValue, comparisonIndex + 1, pendIndex);
                else
                    moveToPend(main, pend, pairValue, comparisonIndex - pairValue + 1, pendIndex);
            }
            comparisonIndex += pairValue;
            pendIndex++;
        }
        giveIndexes(main, pairValue);
        if (COMMENTS)
        {
            std::cout << "indexes in the pend: ";
            printIndexes(pend);
            std::cout << "indexes in the main: ";
            printIndexes(main);
        }
        insertBackToMain(main, pend, pairValue);
        if (COMMENTS)
            printContainerContents(main);
    }
};

void moveToPend(std::vector<PmergeMe>& main, std::vector<PmergeMe>& pend, const size_t& pairValue, const size_t& moveIndex, const size_t& pendIndex)
{
    auto it = main.begin();
    std::advance(it, moveIndex);
    for (size_t i = 0; i < pairValue; i++)
    {
        it->setIndex(pendIndex);
        it->setLetter('B');
        pend.push_back(*it);
        it = main.erase(it);
    }
    if (COMMENTS)
    {
        std::cout << "in the pend now: ";
        printContainerContents(pend);
        std::cout << "in the main now: ";
        printContainerContents(main);
    }
};

void giveIndexes(std::vector<PmergeMe>& main, const size_t& pairValue)
{
    //special case for the first element in the main
    for (size_t i = 0; i < pairValue; i++)
    {
        main.at(i).setIndex(1);
        main.at(i).setLetter('B');
    }
    //give indexes to other elements left in the the main
    int index = 1;
    for (size_t i = pairValue, pair = 0; i < main.size(); i++)
    {
        main.at(i).setIndex(index);
        main.at(i).setLetter('A');
        pair++;
        if (pair == pairValue)
        {
            pair = 0;
            index++;
        }
    }
};

void insertBackToMain(std::vector<PmergeMe>& main, std::vector<PmergeMe>& pend, const size_t& pairValue)
{
    std::vector<int> jacobsthal = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461};

    for (size_t jacobIndex = 1; pend.empty() == false; jacobIndex++)
    {
        const_iterator_vector elementCompPos = findNextPosition(pend, jacobsthal.at(jacobIndex), pairValue);
        const_iterator_vector elementMovePos = elementCompPos - (pairValue  - 1);
        const_iterator_vector lastPos = findLastPosition(pend, jacobsthal.at(jacobIndex - 1) + 1);
        if (COMMENTS)
        {
            std::cout << "TARGET INDEX = " << elementCompPos->getLetter() << elementCompPos->getIndex() << std::endl;
            std::cout << "COMP VALUE = " << elementCompPos->getValue() << std::endl;
            std::cout << "FIRST TO MOVE = " << elementMovePos->getValue() << std::endl;
            std::cout << "LAST VALUE = " << lastPos->getValue() << std::endl;
        }
        while (elementCompPos >= lastPos)
        {
            const_iterator_vector insertPos = findTargetPosition(main, *elementCompPos, pairValue);
            const_iterator_vector lastElem = elementMovePos + pairValue;
            if (COMMENTS)
                std::cout << "inserting values starting from " << elementMovePos->getValue() << " into index " << insertPos->getIndex() << std::endl;
            main.insert(insertPos, elementMovePos, lastElem);
            elementMovePos = pend.erase(elementMovePos, lastElem);
            // move to next element
            elementCompPos -= pairValue;
            if (pend.empty() == false)
                elementMovePos = elementCompPos - (pairValue  - 1);
            if (COMMENTS)
            {
                std::cout << "in the pend now: ";
                printContainerContents(pend);
                std::cout << "in the main now: ";
                printContainerContents(main);
                std::cout << "indexes in the pend: ";
                printIndexes(pend);
                std::cout << "indexes in the main: ";
                printIndexes(main);
            }
        }
    }
};

const_iterator_vector findNextPosition(std::vector<PmergeMe>& pend, const int& jacobNumber, const size_t& pairValue)
{
    for (auto it = pend.begin(); it < pend.end(); it++)
    {
        if (it->getIndex() == jacobNumber)
            return it + (pairValue - 1);
    }
    return pend.end() - 1;
};

const_iterator_vector findLastPosition(std::vector<PmergeMe>& pend, const int& jacobNumber)
{
    for (auto it = pend.begin(); it < pend.end(); it++)
    {
        if (it->getIndex() == jacobNumber)
            return it;
    }
    return pend.begin();
};

const_iterator_vector findTargetPosition(std::vector<PmergeMe>& main, const PmergeMe& element, const size_t& pairValue)
{
    auto it = main.begin() + pairValue - 1;
    for (; it < main.end(); it += pairValue)
    {
        if (it >= main.end())
            break ;
        if (COMMENTS)
            std::cout << "finding target... comparing " << element.getValue() << " with " << it->getValue() << std::endl;
        if (!compare(element, *it))
        {
            if (COMMENTS)
                std::cout << "bigger value found\n";
            return it - (pairValue - 1);
        }
        if (element.getIndex() == it->getIndex() - 1 && it->getLetter() == 'A')
        { 
            if (COMMENTS)
                std::cout << "limit found\n";
            return it - (pairValue - 1);
        }
    }
    if (COMMENTS)
        std::cout << "end reached\n";
    return it - (pairValue - 1);
};