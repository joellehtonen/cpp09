#include "BitcoinExchange.hpp"

int main(int ac, char** av)
{
	if (ac != 2 || !av)
	{
		std::cerr << "Error. Input parameters are incorrect" << std::endl;
		return -1;
	}
	BitcoinExchange *rate = new BitcoinExchange();
	rate->convert(av[1]);



	delete rate;
}