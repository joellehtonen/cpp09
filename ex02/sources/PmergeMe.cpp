#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe() { 
    value = 0;
    rank = 1;
    bigger = false;
};
PmergeMe::PmergeMe(std::string paramValue) { 
    value = stoi(paramValue);
    rank = 1;
    bigger = false;
};
PmergeMe::~PmergeMe() { };
PmergeMe::PmergeMe(const PmergeMe& copy) { 
    value = copy.value;
    rank = copy.rank;
    bigger = copy.bigger;
};
PmergeMe& PmergeMe::operator=(const PmergeMe& copy) {
    if (this != &copy)
    {
        value = copy.value;
        rank = copy.rank;
        bigger = copy.bigger;
    }
    return *this;
};
int PmergeMe::getValue() const {
    return value;
};
void PmergeMe::setValue(int paramValue) {
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
void PmergeMe::setBigger(bool paramBigger) {
    bigger = paramBigger;
};