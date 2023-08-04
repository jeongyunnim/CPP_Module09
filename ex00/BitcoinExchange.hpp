#pragma once
#ifndef _BITCOIN_EXCHANGE_
#define _BITCOIN_EXCHANGE_

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Colors.hpp"

class BitcoinExchange
{
    // 2008/08/18일 이전 예외처리
public:

    static bool databaseToMap(std::ifstream& database);
    static bool parsingDataFile(const std::string& fileName);
    static bool parsingInputFile(const std::string& fileName);
    static void printExchangeRate(const std::string& date, const std::string& value);

private:

    BitcoinExchange(void);
    ~BitcoinExchange(void);
    BitcoinExchange& operator=(const BitcoinExchange& rhs);
    BitcoinExchange(const BitcoinExchange& obj);

    static std::map<std::string, double> _exchangeRateData;

};

#endif
