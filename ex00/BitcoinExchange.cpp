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
		int keyInt = convertStringtoInt(keyString);
		std::string valueString = line.substr(delim + 1);
		float valueFloat = stof(valueString);
		this->_data[keyInt] = valueFloat;
	}
	dataStream.close(); //will this leak in case error is thrown?
};


//TODO REFACTOR THIS
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
			printError(); //make specific error codes later
			continue ;
		}
		std::string keyString = line.substr(0, delim);
		if (keyString.empty() == true)
		{
			printError();
			continue ;
		}
		checkValidDate(keyString);
		// tm dateCheck;
		// inputStream >> std::get_time(&dateCheck, "%Y-%m-%d");
		int keyInt = convertStringtoInt(keyString);
		std::string valueString = line.substr(delim + 1);
		try {	
			float valueFloat = stof(valueString);
			processInput(keyInt, valueFloat);
		}
		catch (...) {
			printError(); //make specific error codes later
			continue ;
		}
	}
	inputStream.close();
};

void BitcoinExchange::checkValidDate(std::string keyString) {
	
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

void BitcoinExchange::processInput(int key, float value)
{
	std::map<int, float>::const_reverse_iterator dataIt = _data.crbegin();
	//TODO check for invalid date (use gettime), if so print error and continue to next line
	while (dataIt != _data.crend() && key < dataIt->first)
		dataIt++;
	if (dataIt == _data.crend())
		dataIt = _data.crbegin();
	if (value < 0 )
		printError(); //make specific error codes later
	else if (value >= INT_MAX)
		printError(); //make specific error codes later
	else
	{
		printDate(key);
		printEquation(value, dataIt);
	}
}

void BitcoinExchange::printDate(int key)
{
	std::string keyString = std::to_string(key);
	for (size_t i = 0; i < keyString.length(); i++)
	{
		std::cout << keyString[i];
		if (i == 3 || i == 5)
			std::cout << '-';
	}
}

void BitcoinExchange::printEquation(float value, std::map<int,float>::const_reverse_iterator dataIt)
{
	float result = value * dataIt->second;
	std::cout << " => " << value << " = " << result << "\n";
	//check width of the float, so all decimals get printed
}

void BitcoinExchange::printError() {
	std::cout << "Error: bad input\n";
};