#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() { };
BitcoinExchange::~BitcoinExchange() { };
BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy) 
: _data(copy._data) { };
const BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy) {
	if (this != &copy)
	{
		this->_data = copy._data;
	}
	return *this;
};

void BitcoinExchange::exchange(const std::string& input) {
	copyDatabase();
	readInput(input);
}

void BitcoinExchange::copyDatabase() {
	bool firstLine = false;

	std::ifstream dataStream("data.csv");
	if (dataStream.is_open() == false)
		throw std::runtime_error("Database could not be opened");
	std::string line;
	while (getline(dataStream, line))
	{
		if (firstLine == false)
		{
			firstLine = true;
			if (line.find("date") != std::string::npos && line.find("exchange_rate") != std::string::npos)
				continue ;
		}
		size_t delim = line.find(',');
		if (delim == std::string::npos)
			throw std::runtime_error("Database incorrectly formatted");
		std::string keyString = line.substr(0, delim);
		if (keyString.empty() == true)
			break ;
		int keyInt = convertStringToInt(keyString);
		std::string valueString = line.substr(delim + 1);
		float valueFloat = stof(valueString);
		this->_data[keyInt] = valueFloat;
	}
	dataStream.close();
};

void BitcoinExchange::readInput(const std::string& input)
{
	bool firstLine = false;

	std::ifstream inputStream(input);
	if (inputStream.is_open() == false)
		throw std::runtime_error("The input could not be opened");
	std::string line;
	while (getline(inputStream, line))
	{
		if (firstLine == false)
		{
			firstLine = true;
			if (line.find("date") != std::string::npos && line.find("value") != std::string::npos)
				continue ;
		}
		size_t delim = line.find('|');
		if (delim == std::string::npos)
		{
			printError(ERROR_DELIM_MISSING);
			continue ;
		}
		std::string keyString = line.substr(0, delim);
		if (keyString.length() != 11)
		{
			printError(ERROR_DATE_FORMAT);
			continue ;
		}
		if (checkIfDateValid(keyString) == false)
		{
			printError(ERROR_DATE_INVALID);
			continue ;
		}
		int keyInt = convertStringToInt(keyString);
		std::string valueString = line.substr(delim + 1);
		try {	
			float valueFloat = stof(valueString);
			processInput(keyInt, valueFloat, keyString);
		}
		catch (...) {
			printError(ERROR_BAD_INPUT);
			continue ;
		}
	}
	inputStream.close();
};

bool BitcoinExchange::checkIfDateValid(const std::string& keyString) 
{
	std::istringstream copyStream(keyString);
	tm date = {};
	copyStream >> std::get_time(&date, "%Y-%m-%d");
	if (checkDateFormat(date) == false)
		return false;
	if (checkIfFutureDate(date) == true)
		return false;
	if (date.tm_year < 2008 - 1900)
		return false;
	return true;
};

bool BitcoinExchange::checkDateFormat(tm date1)
{
	tm date2 = date1;
	time_t time = mktime(&date1);
	if (time == -1)
		return false;
	if (date1.tm_year != date2.tm_year
		|| date1.tm_mon != date2.tm_mon
		|| date1.tm_mday != date2.tm_mday)
	{
		return false;
	}
	return true;
};

bool BitcoinExchange::checkIfFutureDate(tm ref)
{
	std::time_t now = std::time(nullptr);
	tm today = *std::localtime(&now);
	if (ref.tm_year > today.tm_year)
		return true;
	if (ref.tm_year == today.tm_year
		&& ref.tm_mon > today.tm_mon)
		return true;
	if (ref.tm_year == today.tm_year
		&& ref.tm_mon == today.tm_mon
		&& ref.tm_mday > today.tm_mday)
		return true;
	return false;
};

int BitcoinExchange::convertStringToInt(std::string& keyString)
{
	for (size_t i = keyString.find_first_not_of("0123456789"); 
		i != std::string::npos; 
		i = keyString.find_first_not_of("0123456789"))
	{
		keyString.erase(i, 1);
	}
	return stoi(keyString);
};

void BitcoinExchange::processInput(const int& key, const float& value, const std::string& keyString)
{
	std::map<int, float>::const_reverse_iterator dataIt = _data.crbegin();
	while (dataIt != _data.crend() && key < dataIt->first)
		dataIt++;
	if (value < 0 )
		printError(ERROR_NOT_POSITIVE);
	else if (value > 1000)
		printError(ERROR_INT_MAX);
	else
	{
		printDate(keyString);
		printEquation(value, dataIt);
	}
};

void BitcoinExchange::printDate(const std::string& keyString)
{
	for (size_t i = 0; i < keyString.length(); i++)
	{
		std::cout << keyString[i];
		if (i == 3 || i == 5)
			std::cout << '-';
	}
};

void BitcoinExchange::printEquation(const float& value, std::map<int,float>::const_reverse_iterator& dataIt)
{
	float result = value * dataIt->second;
	std::cout << " => " << value << " = " << result << "\n";
}

void BitcoinExchange::printError(std::string errorMessage) {
	std::cout << "Error: " << errorMessage << std::endl;
};