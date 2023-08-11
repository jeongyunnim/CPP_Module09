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

    static BitcoinExchange *getInstence(void);
    static void             cleanUp(void);
    bool parsingDataFile(const std::string& fileName);
    bool parsingInputFile(const std::string& fileName);

private:

    BitcoinExchange(void);
    ~BitcoinExchange(void);
    BitcoinExchange& operator=(const BitcoinExchange& rhs);
    BitcoinExchange(const BitcoinExchange& obj);

    static BitcoinExchange *_exchanger;
    std::map<std::string, double> _exchangeRateData;
    bool databaseToMap(std::ifstream& database);
    void printExchangeRates(std::ifstream& input);
    
};

#endif
