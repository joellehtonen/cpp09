#include "BitcoinExchange.hpp"

int main(int ac, char** av)
{
	if (ac != 2 || !av)
	{
		std::cerr << "Error. Input parameters are incorrect. Remember to add the file" << std::endl;
		return -1;
	}
	BitcoinExchange *rate = new BitcoinExchange();
	try {
		rate->exchange(av[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error. " << e.what() << std::endl;
	}
	delete rate;
}