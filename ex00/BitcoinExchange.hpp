#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <cctype>
#include <climits>
#include <ctime>
#include <iomanip>
#include <algorithm>
#define ERROR_NOT_POSITIVE "not a positive number"
#define ERROR_INT_MAX "too large a number"
#define ERROR_DATE_INVALID "date invalid"
#define ERROR_DATE_FORMAT "date format incorrect: YYYY-MM-DD"
#define ERROR_BAD_INPUT "bad input"
#define ERROR_DELIM_MISSING "delimiter missing"

class BitcoinExchange {
	private:
		std::map<int,float>	_data;

		void	copyDatabase();
		void	readInput(const std::string& input);
		bool	checkIfDateValid(const std::string& keyString);
		bool 	checkDateFormat(tm date1);
		bool	checkIfFutureDate(tm ref);
		int		convertStringToInt(std::string& string);
		void	processInput(const int& key, const float& value, const std::string& keyString);
		void	printError(std::string errorMessage);
		void	printDate(const std::string& keyString);
		void	printEquation(const float& value, std::map<int,float>::const_reverse_iterator& dataIt);
	
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& copy);
		const BitcoinExchange& operator=(const BitcoinExchange& copy);

		void exchange(const std::string& input);

	
};