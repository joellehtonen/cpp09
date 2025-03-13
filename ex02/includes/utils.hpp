#pragma once
#include "PmergeMe.hpp"
#include <vector>
#include <list>
#include <iomanip>
typedef std::vector<PmergeMe>::const_iterator const_iterator;

void	sortVector(std::vector<PmergeMe>& container);
void	firstComparison(std::vector<PmergeMe>& container);
size_t	formPairs(std::vector<PmergeMe>& container);
void	comparePairs(std::vector<PmergeMe>& container, size_t& i, size_t& pairValue);
void	insertion(std::vector<PmergeMe>& container, size_t& pairValue);
void    moveToPend(std::vector<PmergeMe>& container, std::vector<PmergeMe>& pend, const size_t& pairValue, const size_t& moveIndex, const size_t& pendIndex);
void    giveIndexes(std::vector<PmergeMe>& container, const size_t& pairValue);
void    insertBackToMain(std::vector<PmergeMe>& container, std::vector<PmergeMe>& pend, const size_t& pairValue);
const_iterator    findNextPosition(std::vector<PmergeMe>& pend, const int& jacobNumber, const size_t& pairValue);
const_iterator    findLastPosition(std::vector<PmergeMe>& pend, const int& jacobNumber);
const_iterator    findTargetPosition(std::vector<PmergeMe>& container, const PmergeMe& element, const size_t& pairValue);

template <typename T>
void giveNewRanks(T& container, int pairValue);

template <typename T>
void updateGroups(T& container, int pairValue);

template <typename T>
void printGroups(const T& container);

template <typename T>
void printContainerContents(const T& container);

#include "../sources/utils.tpp"