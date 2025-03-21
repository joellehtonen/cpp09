#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

// comparing/swapping each number (1), then pair (2), and then pair of pairs (4), etc, 8, 16, 32... 
void sortList(std::list<PmergeMe>& container)
{
    firstComparison(container);
    size_t pairValue = formPairs(container);
    if (COMMENTS)
    {
        printGroups(container);
        printComparisonAmount();
    }
    insertion(container, pairValue);
    printComparisonAmount();
};

void firstComparison(std::list<PmergeMe>& container)
{
    for (auto it = container.begin(); it != container.end();)
    {
        auto next = std::next(it);
        if (next == container.end())
            break ;
        if (COMMENTS)
            std::cout << "comparing " << it->getValue() << " with " << next->getValue() << "\n";
        if (compare(*it, *next))
        {
            std::swap(*it, *next);
            if (COMMENTS)
                std::cout << "swap\n";
        }
        std::advance(it, 2);
    }
};

size_t formPairs(std::list<PmergeMe>& container)
{
    if (COMMENTS)
        printContainerContents(container);
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
            printContainerContents(container);
    }
    return pairValue / 2;
};

void comparePairs(std::list<PmergeMe>& container, size_t& i, size_t& pairValue)
{
    auto firstPairIterator = container.begin();
    std::advance(firstPairIterator, i + pairValue - 1);

    auto secondPairIterator = container.begin();
    std::advance(secondPairIterator, i + pairValue * 2 - 1);

    if (COMMENTS)
        std::cout << "comparing " << firstPairIterator->getValue() << " with " << secondPairIterator->getValue() << "\n";
    if (compare(*firstPairIterator, *secondPairIterator))
    {
        if (COMMENTS)
            std::cout << "swapping\n";
        std::advance(firstPairIterator, -(pairValue - 1));
        std::advance(secondPairIterator, -(pairValue - 1));
        for (size_t j = 0; j < pairValue; j++)
        {
            std::swap(*firstPairIterator, *secondPairIterator);
            firstPairIterator++;
            secondPairIterator++;
        }
    }
};

void insertion(std::list<PmergeMe>& main, size_t& pairValue)
{
    std::list<PmergeMe> pend;

    for (; pairValue >= 1; pairValue /= 2)
    {
        if (COMMENTS)
            std::cout << "PAIR VALUE = " << pairValue << std::endl;
        size_t comparisonIndex = pairValue * 3 - 1;
        if (comparisonIndex > main.size())
            continue ;
        size_t pendIndex = 2;
        auto it = main.begin();
        std::advance(it, comparisonIndex);
        auto it2 = it;
        std::advance(it2, pairValue);
        while (comparisonIndex < main.size())
        {
            if (comparisonIndex + pairValue >= main.size())
            {
                if (COMMENTS)
                    std::cout << "moving " << it->getValue() << " to pend\n";
                moveToPend(main, pend, pairValue, comparisonIndex - pairValue + 1, pendIndex);
            }
            else
            {
                if (COMMENTS)
                    std::cout << "comparing " << it->getValue() << " with " << it2->getValue() << std::endl;
                if (compare(*it, *it2))
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

void moveToPend(std::list<PmergeMe>& main, std::list<PmergeMe>& pend, const size_t& pairValue, const size_t& moveIndex, const size_t& pendIndex)
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

void giveIndexes(std::list<PmergeMe>& main, const size_t& pairValue)
{
    //special case for the first element in the main
    auto it = main.begin();
    for (size_t i = 0; i < pairValue && it != main.end(); i++, it++)
    {
        it->setIndex(1);
        it->setLetter('B');
    }
    //give indexes to other elements left in the the main
    int index = 1;
    size_t pair = 0;
    for (; it != main.end(); it++)
    {
        it->setIndex(index);
        it->setLetter('A');
        pair++;
        if (pair == pairValue)
        {
            pair = 0;
            index++;
        }
    }
};

void insertBackToMain(std::list<PmergeMe>& main, std::list<PmergeMe>& pend, const size_t& pairValue)
{
    std::vector<int> jacobsthal = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461};

    for (size_t jacobIndex = 1; pend.empty() == false; jacobIndex++)
    {
        const_iterator_list elementCompPos = findNextPosition(pend, jacobsthal.at(jacobIndex), pairValue);
        const_iterator_list elementMovePos = elementCompPos;
        std::advance(elementMovePos, -(pairValue - 1));
        const_iterator_list lastPos = findLastPosition(pend, jacobsthal.at(jacobIndex - 1) + 1);
        if (COMMENTS)
        {
            std::cout << "TARGET INDEX = " << elementCompPos->getLetter() << elementCompPos->getIndex() << std::endl;
            std::cout << "COMP VALUE = " << elementCompPos->getValue() << std::endl;
            std::cout << "FIRST TO MOVE = " << elementMovePos->getValue() << std::endl;
            std::cout << "LAST VALUE = " << lastPos->getValue() << std::endl;
        }
        while (elementMovePos != pend.end() && std::distance(lastPos, elementMovePos) >= 0)
        {
            const_iterator_list insertPos = findTargetPosition(main, *elementCompPos, pairValue);
            for (size_t i = 0; i < pairValue; i++)
            {
                if (COMMENTS)
                    std::cout << "inserting " << elementMovePos->getValue() << " into index " << insertPos->getIndex() << std::endl;
                main.insert(insertPos, *elementMovePos);
                elementMovePos = pend.erase(elementMovePos);
            }
            std::cout << "moving on...\n";
            std::cout << "compPos point to " << elementCompPos->getValue() << std::endl;
            std::cout << "movePos point to " << elementMovePos->getValue() << std::endl;
            // if (pend.empty() == false)
            // {
            //     std::advance(elementCompPos, -pairValue);
            //     elementMovePos = elementCompPos;
            //     std::advance(elementMovePos, -(pairValue - 1));
            // }
            if (COMMENTS)
            {
                std::cout << "in the pend now:     ";
                printContainerContents(pend);
                std::cout << "in the main now:     ";
                printContainerContents(main);
                std::cout << "indexes in the pend: ";
                printIndexes(pend);
                std::cout << "indexes in the main: ";
                printIndexes(main);
            }
        }
    }
};

const_iterator_list findNextPosition(std::list<PmergeMe>& pend, const int& jacobNumber, const size_t& pairValue)
{
    for (auto it = pend.begin(); it != pend.end(); it++)
    {
        if (it->getIndex() == jacobNumber)
        {
            int move = pairValue - 1;
            std::advance(it, move);
            return it;
        }
    }
    auto end = pend.end();
    std::advance(end, -1);
    return end;
};

const_iterator_list findLastPosition(std::list<PmergeMe>& pend, const int& jacobNumber)
{
    for (auto it = pend.begin(); it != pend.end(); it++)
    {
        if (it->getIndex() == jacobNumber)
            return it;
    }
    return pend.begin();
};

const_iterator_list findTargetPosition(std::list<PmergeMe>& main, const PmergeMe& element, const size_t& pairValue)
{
    auto it = main.begin();
    std::advance(it, (pairValue - 1));
    for (; it != main.end(); std::advance(it, pairValue))
    {
        if (std::distance(it, main.end()) <= 0)
            break ;
        if (COMMENTS)
            std::cout << "finding target... comparing " << element.getValue() << " with " << it->getValue() << std::endl;
        if (!compare(element, *it))
        {
            if (COMMENTS)
                std::cout << "bigger value found\n";
            std::advance(it, -(pairValue - 1));
            return it;
        }
        if (element.getIndex() == it->getIndex() && it->getLetter() == 'A')
        { 
            if (COMMENTS)
                std::cout << "limit found\n";
            std::advance(it, -(pairValue - 1));
            return it;
        }
        auto check = it;
        for (size_t i = 0; i < pairValue; i++)
        {
            std::advance(check, 1);
            if (check == main.end())
                break ;
        }
    }
    if (COMMENTS)
        std::cout << "end reached\n";
    return it;
};