#pragma once
#include <string>
#include <iostream>

class PmergeMe
{
    private:
        int value;
        int rank;
        int bigger;

    public:
        PmergeMe();
        PmergeMe(std::string value);
        ~PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& copy);

        int     getValue() const;
        int     getRank() const;
        bool    getBigger() const;
        void    setValue(int paramValue);
        void    setRank(int paramRank);
        void    setBigger(bool paramBigger);
};