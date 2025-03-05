#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <cctype>
#include <algorithm>

class BitcoinExchange {
	private:
		std::map<int,float>	_data;
		std::map<int,float>	_input;
		bool				_firstLineChecked;

		void	copyDatabase();
		void	copyInput(const std::string& input);
		int		convertStringtoInt(std::string& string);
		void	lineByLine();
		void	printDate(std::map<int,float>::const_iterator it);
		void	printEquation(std::map<int,float>::const_iterator inputIt, std::map<int,float>::const_reverse_iterator dataIt);
	
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& copy);
		const BitcoinExchange& operator=(const BitcoinExchange& copy);

		void exchange(const std::string& input);

	
};