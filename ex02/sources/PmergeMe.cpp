#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe() { 
    value = 0;
    rank = 1;
    index = 0;
    letter = 'X';
};
PmergeMe::PmergeMe(std::string paramValue) { 
    value = stoi(paramValue);
    rank = 1;
    index = 0;
    letter = 'X';
};
PmergeMe::~PmergeMe() { };
PmergeMe::PmergeMe(const PmergeMe& copy) { 
    value = copy.value;
    rank = copy.rank;
    index = copy.index;
    letter = copy.letter;
    group = copy.group;
};
PmergeMe& PmergeMe::operator=(const PmergeMe& copy) {
    if (this != &copy)
    {
        value = copy.value;
        rank = copy.rank;
        index = copy.index;
        letter = copy.letter;
        group = copy.group;
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
int PmergeMe::getIndex() const {
    return index;
};
void PmergeMe::setIndex(int paramIndex) {
    index = paramIndex;
};
char PmergeMe::getLetter() const {
    return letter;
};
void PmergeMe::setLetter(char paramLetter) {
    letter = paramLetter;
};
std::vector<int> PmergeMe::getGroup() const {
    return group;
};
void PmergeMe::addGroup(int newGroup) {
    group.push_back(newGroup);
};