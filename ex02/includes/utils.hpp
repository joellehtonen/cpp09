#pragma once
#include "PmergeMe.hpp"
#include <vector>
#include <list>
#include <iomanip>
#include <algorithm>
#include <chrono>
#define COMMENTS 0

typedef std::vector<PmergeMe>::const_iterator const_iterator_vector;
typedef std::list<PmergeMe>::const_iterator const_iterator_list;

// VECTOR FUNCTIONS
void	sortVector(std::vector<PmergeMe>& container);
void	firstComparison(std::vector<PmergeMe>& container);
size_t	formPairs(std::vector<PmergeMe>& container);
void	comparePairs(std::vector<PmergeMe>& container, size_t& i, size_t& pairValue);
void	insertion(std::vector<PmergeMe>& main, size_t& pairValue);
void    moveToPend(std::vector<PmergeMe>& main, std::vector<PmergeMe>& pend, const size_t& pairValue, const size_t& moveIndex, const size_t& pendIndex);
void    giveIndexes(std::vector<PmergeMe>& main, const size_t& pairValue);
void    insertBackToMain(std::vector<PmergeMe>& main, std::vector<PmergeMe>& pend, const size_t& pairValue);
const_iterator_vector	findNextPosition(std::vector<PmergeMe>& pend, const int& jacobNumber, const size_t& pairValue);
const_iterator_vector	findLastPosition(std::vector<PmergeMe>& pend, const int& jacobNumber);
const_iterator_vector	findTargetPosition(std::vector<PmergeMe>& main, const PmergeMe& element, const size_t& pairValue);
const_iterator_vector	findLimit(std::vector<PmergeMe>& main, const PmergeMe& element, const size_t& pairValue);

// LIST FUNCTIONS
void 	sortList(std::list<PmergeMe>& container);
void	firstComparison(std::list<PmergeMe>& container);
size_t	formPairs(std::list<PmergeMe>& container);
void	comparePairs(std::list<PmergeMe>& container, size_t& i, size_t& pairValue);
void	insertion(std::list<PmergeMe>& main, size_t& pairValue);
void    moveToPend(std::list<PmergeMe>& main, std::list<PmergeMe>& pend, const size_t& pairValue, const size_t& moveIndex, const size_t& pendIndex);
void    giveIndexes(std::list<PmergeMe>& main, const size_t& pairValue);
void    insertBackToMain(std::list<PmergeMe>& main, std::list<PmergeMe>& pend, const size_t& pairValue);
void 	handleRemainingElement(std::list<PmergeMe>& main, std::list<PmergeMe>& pend, const_iterator_list insertThis);
const_iterator_list	findNextPosition(std::list<PmergeMe>& pend, const int& jacobNumber, const size_t& pairValue);
const_iterator_list findLastPosition(std::list<PmergeMe>& pend, const int& jacobNumber);
const_iterator_list	findTargetPosition(std::list<PmergeMe>& main, const PmergeMe& element, const size_t& pairValue);
const_iterator_list	findLimit(std::list<PmergeMe>& main, const PmergeMe& element, const size_t& pairValue);

// CHECKERS
bool checkDigits(int ac, char**av);
bool checkDuplicates(int ac, char** av);
bool checkOrder(int ac, char** av);

// TEMPLATES
template <typename T>
void giveNewRanks(T& container, int pairValue);

template <typename T>
void updateGroups(T& container, int pairValue);

template <typename T>
void printGroups(const T& container);

template <typename T>
void printIndexes(const T& container);

template <typename T>
void printContainerContents(const T& container);

template <typename T>
bool checkResultOrder(const T& container);

// COMPARE
bool compare(const PmergeMe& ref1, const PmergeMe& ref2);
void resetComparisons();
void printComparisonAmount();

#include "../sources/utils.tpp"