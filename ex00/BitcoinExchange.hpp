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
		std::map<std::string, float> _data;
		std::map<std::string, float> _input;
	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& copy);
		const BitcoinExchange& operator=(const BitcoinExchange& copy);

		void copyDatabase();
		void convert(const std::string& input);
		void copyInput(const std::string& input);
};