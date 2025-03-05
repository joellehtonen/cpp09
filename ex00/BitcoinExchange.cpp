#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	_firstLineChecked = false;
};
BitcoinExchange::~BitcoinExchange() { };
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

void BitcoinExchange::exchange(const std::string& input) {
	copyDatabase();
	copyInput(input);
	// auto it = _data.begin();
	// std::cout << "database #0 = " << it->first << " | " << it->second << std::endl;
	// it++;
	// std::cout << "database #1 = " << it->first << " | " << it->second << std::endl;
	// it = _input.begin();
	// std::cout << "input #0 = " << it->first << " | " << it->second << std::endl;
	// it++;
	// std::cout << "input #1 = " << it->first << " | " << it->second << std::endl;
	lineByLine();
};

void BitcoinExchange::copyDatabase() {
	std::ifstream dataStream("data.csv");
	if (dataStream.is_open() == false)
		throw std::runtime_error("The database could not be opened");
	std::string line;
	while (getline(dataStream, line))
	{
		if (_firstLineChecked == false)
		{
			if (line.find("date") != std::string::npos && line.find("exchange_rate") != std::string::npos)
			{
				_firstLineChecked = true;
				continue ;
			}
			_firstLineChecked = true;
		}
		size_t delim = line.find(',');
		if (delim == std::string::npos)
			throw std::runtime_error("Database incorrectly formatted");
		std::string keyString = line.substr(0, delim);
		int keyInt = convertStringtoInt(keyString);
		std::string valueString = line.substr(delim + 1);
		float valueFloat = stof(valueString);
		this->_data[keyInt] = valueFloat;
	}
	dataStream.close(); //will this leak in case error is thrown?
};

void BitcoinExchange::copyInput(const std::string& input)
{
	std::ifstream inputStream(input);
	if (inputStream.is_open() == false)
		throw std::runtime_error("The input could not be opened");
	std::string line;
	while (getline(inputStream, line))
	{
		size_t delim = line.find('|');
		if (delim == std::string::npos)
		{
			// this->_input[line + "_INPUT_ERROR"]; // handle more comprehensively later
			continue ;
		}
		std::string keyString = line.substr(0, delim);
		int keyInt = convertStringtoInt(keyString);
		std::string valueString = line.substr(delim + 1);
		try {	
			float valueFloat = stof(valueString);
			this->_input[keyInt] = valueFloat;
		}
		catch (...) {
			//this->_input[line + "_FLOAT_ERROR"];
			continue ;
		}
	}
	inputStream.close();
};

int BitcoinExchange::convertStringtoInt(std::string& keyString)
{
	for (size_t i = keyString.find_first_not_of("0123456789"); 
		i != std::string::npos; 
		i = keyString.find_first_not_of("0123456789"))
	{
		keyString.erase(i, 1);
	}
	return stoi(keyString);
}

void BitcoinExchange::lineByLine()
{
	std::map<int, float>::const_iterator inputIt = _input.begin();
	while (inputIt != _input.end())
	{
		//TODO check for invalid date (use gettime), if so print error and continue to next line
		std::map<int, float>::const_reverse_iterator dataIt = _data.crbegin();
		while (inputIt->first > dataIt->first)
			dataIt++;
		//TODO check for invalid format, if so print error
		printDate(inputIt);
		printEquation(inputIt, dataIt);
		inputIt++;
	}
}

void BitcoinExchange::printDate(std::map<int, float>::const_iterator it)
{
	std::string keyString = std::to_string(it->first);
	for (int i = 0; i < 4; i++)
		std::cout << keyString[i];
	std::cout << '-';
	for (int i = 4; i < 6; i++)
		std::cout << keyString[i];
	std::cout << '-';
	for (int i = 6; i < 8; i++)
		std::cout << keyString[i];
}

void BitcoinExchange::printEquation(std::map<int,float>::const_iterator inputIt, std::map<int,float>::const_reverse_iterator dataIt)
{
	float result = inputIt->second * dataIt->second;
	std::cout << "\n\n TEST \n\n";
	std::cout << "input second = " << inputIt->second << " data second = " << dataIt->second;
	std::cout << "\n\n";
	std::cout << " => " << inputIt->second << " = " << result << "\n";
	//check width of the float, so all decimals get printed
}