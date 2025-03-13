#pragma once
#include <string>
#include <iostream>
#include <vector>

class PmergeMe
{
    private:
        int                 value;
        int                 rank; //mostly for demonstration
        std::vector<int>    group; //mostly for demonstration
        int                 index;
        char                letter;


    public:
        PmergeMe();
        PmergeMe(std::string value);
        ~PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& copy);

        int                 getValue() const;
        int                 getRank() const;
        std::vector<int>    getGroup() const;
        int                 getIndex() const;
        char                getLetter() const;
        void    setValue(int paramValue);
        void    setRank(int paramRank);
        void    addGroup(int newGroup);
        void    setIndex(int paramIndex);
        void    setLetter(char paramLetter);
};