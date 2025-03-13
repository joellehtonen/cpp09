#pragma once
#include "PmergeMe.hpp"
#include <vector>
#include <list>
#include <iomanip>

void	sortVector(std::vector<PmergeMe>& container);
void	firstComparison(std::vector<PmergeMe>& container);
size_t	formPairs(std::vector<PmergeMe>& container);
void	comparePairs(std::vector<PmergeMe>& container, size_t& i, size_t& pairValue);
void	insertion(std::vector<PmergeMe>& container, size_t pairValue);
void 	moveToPend(std::vector<PmergeMe>& container, std::vector<PmergeMe> pend, size_t pairValue, size_t moveIndex);
void    giveIndexes(std::vector<PmergeMe>& container, std::vector<PmergeMe>& pend, size_t pairValue);
void    insertToMain(std::vector<PmergeMe>& container, std::vector<PmergeMe> pend, size_t pairValue);
size_t  findNextIndex(std::vector<PmergeMe> pend, size_t jacobNumber);

template <typename T>
void giveNewRanks(T& container, int pairValue);

template <typename T>
void updateGroups(T& container, int pairValue);

template <typename T>
void printGroups(const T& container);

template <typename T>
void printContainerContents(const T& container);

#include "../sources/utils.tpp"