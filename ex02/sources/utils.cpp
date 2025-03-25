#include "../includes/PmergeMe.hpp"
#include "../includes/utils.hpp"

size_t comparisons = 0;

bool checkDigits(int ac, char**av)
{
	std::string args;
	for (int i = 2; i < ac; i++)
	{
		args += av[i];
	}
	if (args.find_first_not_of("01234567890") != std::string::npos)
		return false;
	return true;
}

bool checkDuplicates(int ac, char** av)
{
	std::vector<int> checked;
	checked.push_back(std::stoi(av[1]));
	for (int i = 2; i < ac; i++)
	{
		if (std::find(checked.begin(), checked.end(), std::stoi(av[i])) != checked.end())
			return false;
		checked.push_back(std::stoi(av[i]));
	}
	return true;
}

bool checkOrder(int ac, char** av)
{
	for (int i = 2; i < ac; i++)
	{
		if (std::stoi(av[i - 1]) > std::stoi(av[i]))
			return true;
	}
	return false;
}

void resetComparisons()
{
	comparisons = 0;
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