#pragma once
#include <string>
#include <iostream>

class PmergeMe
{
    private:
        int value;
        int rank;
        int sorted;
        int bigger;

    public:
        PmergeMe();
        PmergeMe(std::string value);
        ~PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& copy);

        int getValue() const;
        int setValue(int paramValue);
        int getRank() const;
        void setRank(int paramRank);
        bool getSorted() const;
        void setSorted(bool paramSorted);
        bool getBigger() const;
        bool setBigger(bool paramBigger);
};