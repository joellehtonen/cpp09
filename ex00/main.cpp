#include "BitcoinExchange.hpp"

int main(int ac, char** av)
{
	if (ac != 2 || !av)
	{
		std::cerr << "Error. Input parameters are incorrect" << std::endl;
		return -1;
	}
	BitcoinExchange rate(av[1]);



	std::ifstream database("database.csv");
	if (database.is_open() == false)
		throw std::runtime_error("The database could not be opened");
	std::string line;
	while (getline(database, line))
	{

	}
	database.close();
}