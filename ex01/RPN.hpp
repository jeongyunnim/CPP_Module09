#pragma once
#ifndef _RPN_HPP_
#define _RPN_HPP_

#include <iostream>
#include <iomanip>
#include <stack>
#include <algorithm>
#include <sstream>
#include "../Colors.hpp"

class RPN
{

public:

    static bool pushArguments(char *argv[]);
    static bool readOneArg(std::string arg);
    static bool argToStack(const std::string& oneExpression);
    static bool performOperations(int sign);
    static bool printResult(void);

private:

    static bool meetSign(int sign);
    static bool meetNumber(const std::string& numString);

    RPN(void);
    ~RPN(void);
    RPN& operator=(const RPN& rhs);
    RPN(const RPN& obj);

    static std::stack<int>  _numStack;

};

#endif
