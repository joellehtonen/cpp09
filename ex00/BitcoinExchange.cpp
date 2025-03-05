#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
	_firstLineChecked = false;
};
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
	//copyInput(input);
	// auto it = _data.begin();
	// std::cout << "database #0 = " << it->first << " | " << it->second << std::endl;
	// it++;
	// std::cout << "database #1 = " << it->first << " | " << it->second << std::endl;
	// it++;
	// std::cout << "database #2 = " << it->first << " | " << it->second << std::endl;
	// it = _input.begin();
	// std::cout << "input #0 = " << it->first << " | " << it->second << std::endl;
	// it++;
	// std::cout << "input #1 = " << it->first << " | " << it->second << std::endl;
};

void BitcoinExchange::copyDatabase() {
	std::ifstream dataStream("minidata.csv");
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


//TODO REFACTOR THIS
void BitcoinExchange::readInput(const std::string& input)
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
			processInput(0, 0); //make specific error codes later
			continue ;
		}
		std::string keyString = line.substr(0, delim);
		int keyInt = convertStringtoInt(keyString);
		std::string valueString = line.substr(delim + 1);
		try {	
			float valueFloat = stof(valueString);
			processInput(keyInt, valueFloat);
		}
		catch (...) {
			processInput(0, 0); //make specific error codes later
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

void BitcoinExchange::processInput(int key, float value)
{
	// std::map<int, float>::const_iterator inputIt = _input.begin();
	std::map<int, float>::const_reverse_iterator dataIt = _data.crbegin();
	// while (inputIt != _input.end())
	// {
		//TODO check for invalid date (use gettime), if so print error and continue to next line
		while (dataIt != _data.crend() && key > dataIt->first)
			dataIt++;
		//TODO check for invalid format, if so print error
		printDate(key);
		printEquation(value, dataIt);
		// inputIt++;
		dataIt = _data.crbegin();
	// }
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
	//std::cout << " => " << dataIt->second << " = " << result << "\n";
	//check width of the float, so all decimals get printed
}