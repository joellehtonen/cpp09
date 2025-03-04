#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() { };
BitcoinExchange::BitcoinExchange(const std::string& input)
{
	databaseIntoContainer();
	inputIntoContainer(input);


};

BitcoinExchange::~BitcoinExchange() {};


BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) { };
const BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy) {
	if (this != &copy)
	{
		
	}
	return *this;
};

void BitcoinExchange::databaseIntoContainer() {
	std::ifstream dataStream("data.csv");
	if (dataStream.is_open() == false)
		throw std::runtime_error("The database could not be opened");
	std::string line;
	while (getline(dataStream, line))
	{
		int delim = line.find(',');
	}
	dataStream.close();
};

void BitcoinExchange::inputIntoContainer(const std::string& input)
{
	std::ifstream inputStream(input);
	if (inputStream.is_open() == false)
		throw std::runtime_error("The input could not be opened");
	std::string line;
	while (getline(inputStream, line))
	{
		int delim = line.find('|');
		if (delim == std::string::npos)
		{
			this->_input[line + "_INPUT_ERROR"]; // handle more comprehensively later?
			continue ;
		}
		std::string key = line.substr(0, delim);
		std::string stringValue = line.substr(delim + 1);
		for (int i = 0; i < stringValue.length(); i++)
		{
			char c = stringValue[i];
			if (isdigit(c) == false)
			{
				this->_input[line + "_FLOAT_ERROR"];
				continue ;
			}
		}
		float floatValue = std::stof(stringValue);
		this->_input[key] = floatValue;
	}
	inputStream.close();
};