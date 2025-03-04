#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() { };
BitcoinExchange::BitcoinExchange(const std::string& input)
{
	std::ifstream inputStream(input);
	if (inputStream.is_open() == false)
		throw std::runtime_error("The input could not be opened");
	std::string line;
	while (getline(inputStream, line))
	{
		int delim = line.find('|');
		// if (delim == std::string::npos)
		// 	throw std::runtime_error("Incorrect format in the input file"); //cannot throw an error, must record the error in appro line
		std::string key = line.substr(0, delim);
		std::string stringValue = line.substr(delim + 1, line.length() - delim);
		for (int i = 0; i < stringValue.length(); i++)
		{
			char c = stringValue[i];
			if (isdigit(c) == false);
				//write an error to the line
		}
		float floatValue = stof(stringValue);
		this->_input[key] = floatValue;
	}
	inputStream.close();
}
BitcoinExchange::~BitcoinExchange() { };
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) { };
const BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy) {
	if (this != &copy)
	{
		
	}
	return *this;
};