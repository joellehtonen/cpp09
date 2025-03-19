#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

size_t comparisons = 0;

bool checkDuplicates(int ac, char** av)
{
	std::vector<char*> checked;
	checked.push_back(av[1]);
	for (int i = 2; i < ac; i++)
	{
		if (std::find(checked.begin(), checked.end(), av[i]) != checked.end())
			return true;
		checked.push_back(av[i]);
	}
	return false;
}

bool checkOrder(int ac, char** av)
{
	for (int i = 2; i < ac; i++)
	{
		if (av[i - 1] > av[i])
			return false;
	}
	return true;
}

bool compare(const PmergeMe& ref1, const PmergeMe& ref2)
{
	comparisons++;
	if (ref1.getValue() > ref2.getValue())
		return true;
	else
		return false;
}

void printComparisonAmount()
{
	std::cout << "Number of comparisons: " << comparisons << std::endl;
}