#pragma once
#include <string>
#include <iostream>
#include <vector>

class PmergeMe
{
    private:
        int                 value;
        int                 rank;
        std::vector<int>    group;
        bool                bigger;

    public:
        PmergeMe();
        PmergeMe(std::string value);
        ~PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& copy);

        int                 getValue() const;
        int                 getRank() const;
        std::vector<int>    getGroup() const;
        bool                getBigger() const;
        void    setValue(int paramValue);
        void    setRank(int paramRank);
        void    addGroup(int newGroup);
        void    setBigger(bool paramBigger);
};