#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	copyDatabase();
};
BitcoinExchange::~BitcoinExchange() {};
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) 
: _data(copy._data), _input(copy._input) { };
const BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy) {
	if (this != &copy)
	{
		this->_data = copy._data;
		this->_input = copy._input;
	}
	return *this;
};

void BitcoinExchange::copyDatabase() {
	std::ifstream dataStream("data.csv");
	if (dataStream.is_open() == false)
		throw std::runtime_error("The database could not be opened");
	std::string line;
	while (getline(dataStream, line))
	{
		int delim = line.find(',');
		if (delim == std::string::npos)
			throw std::runtime_error("Database incorrectly formatted");
		std::string key = line.substr(0, delim);
		std::string stringValue = line.substr(delim + 1);
		try {
			float floatValue = stof(stringValue);
			this->_data[key] = floatValue;
		}
		catch (...) {
			throw std::runtime_error("Database incorrectly formatted");
		};

	}
	dataStream.close();
};

void BitcoinExchange::convert(const std::string& input) {
	copyInput(input);
};



// remember to test with whitespace
void BitcoinExchange::copyInput(const std::string& input)
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
			this->_input[line + "_INPUT_ERROR"]; // handle more comprehensively later
			continue ;
		}
		std::string key = line.substr(0, delim);
		std::string stringValue = line.substr(delim + 1);
		try {	
			float floatValue = stof(stringValue);
			this->_input[key] = floatValue;
		}
		catch (...) {
			this->_input[line + "_FLOAT_ERROR"];
		}
	}
	inputStream.close();
};