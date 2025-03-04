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

		BitcoinExchange();

	public:
		BitcoinExchange(const std::string& input);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& copy);
		const BitcoinExchange& operator=(const BitcoinExchange& copy);

		const float& getData()const;
};