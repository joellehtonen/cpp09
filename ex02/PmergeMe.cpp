#include "PmergeMe.hpp"

PmergeMe::PmergeMe() { 
    value = 0;
    rank = 0;
    sorted = false;
    bigger = false;
};
PmergeMe::PmergeMe(std::string paramValue) { 
    value = stoi(paramValue);
    rank = 0;
    sorted = false;
    bigger = false;
};
PmergeMe::~PmergeMe() { };
PmergeMe::PmergeMe(const PmergeMe& copy) { 
    value = copy.value;
    rank = copy.rank;
    sorted = copy.sorted;
    bigger = copy.bigger;
};
PmergeMe& PmergeMe::operator=(const PmergeMe& copy) {
    if (this != &copy)
    {
        value = copy.value;
        rank = copy.rank;
        sorted = copy.sorted;
        bigger = copy.bigger;
    }
    return *this;
};

int PmergeMe::getValue() const {
    return value;
};

int PmergeMe::setValue(int paramValue) {
    value = paramValue;
};

int PmergeMe::getRank() const {
    return rank;
};
void PmergeMe::setRank(int paramRank) {
    rank = paramRank;
};
bool PmergeMe::getBigger() const {
    return bigger;
};
bool PmergeMe::setBigger(bool paramBigger) {
    bigger = paramBigger;
};
bool PmergeMe::getSorted() const {
    return sorted;
};
void PmergeMe::setSorted(bool paramSorted) {
    sorted = paramSorted;
};