#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

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