#include "PmergeMe.hpp"
#include "utils.cpp"
#include "sort.cpp"
#include <vector>
#include <deque>

int main (int ac, char** av)
{
    std::vector<PmergeMe>   container1;
    std::deque<PmergeMe>    container2;
    //check if input only valid digits
    //print input
    //start timer
    for (int i = 1; i < ac; i++)
    {
        container1.push_back(PmergeMe(av[i]));
        // if (i % 2 == 0)
        //     container1.at(i).setRank(2);
        // else
        //     container1.at(i).setRank(1);
    }
    sort(container1);
    //stop timer
    //print timer
    //same again with the other container
}

