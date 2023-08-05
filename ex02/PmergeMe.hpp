#pragma once
#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <deque>
#include <list>
#include "../Colors.hpp"

class PmergeMe
{

public:

    static bool pushArguments(char *argv[]);
    static void printArguments(void);

private:

    static bool readOneArg(std::string arg);
    static bool argToContainer(const std::string& oneExpression);
    static bool pushNumber(const std::string& numString);

    PmergeMe(void);
    ~PmergeMe(void);
    PmergeMe& operator=(const PmergeMe& rhs);
    PmergeMe(const PmergeMe& obj);

    static std::deque<int> _argsDeque;
    static std::list<int> _argsList;

};

#endif