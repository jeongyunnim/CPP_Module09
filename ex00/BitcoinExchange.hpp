#pragma once
#ifndef _BITCOIN_EXCHANGE_
#define _BITCOIN_EXCHANGE_

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <sstream>
#include "../Colors.hpp"

class BitcoinExchange
{

public:

    static bool databaseToMap(std::ifstream& database);
    static bool parsingDataFile(const std::string& fileName);
    static bool parsingInputFile(const std::string& fileName);
    static void printExchangeRates(std::ifstream& input);

private:

    BitcoinExchange(void);
    ~BitcoinExchange(void);
    BitcoinExchange& operator=(const BitcoinExchange& rhs);
    BitcoinExchange(const BitcoinExchange& obj);

    static std::map<std::string, double> _exchangeRateData;

};

#endif
