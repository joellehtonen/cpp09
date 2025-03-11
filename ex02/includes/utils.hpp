#pragma once
#include "PmergeMe.hpp"
#include <vector>
#include <list>

void sortVector(std::vector<PmergeMe>& container);
void firstComparison(std::vector<PmergeMe>& container);
//void swapValues(PmergeMe& one, PmergeMe& two);
void comparePairs(std::vector<PmergeMe>& container, size_t& i, size_t& pairValue);

template <typename T>
void giveNewRanks(T& container, int pairValue);

template <typename T>
void uncheckAll(T& container);

template <typename T>
void printContainerContents(const T& container);

#include "../sources/utils.tpp"