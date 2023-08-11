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

    static RPN *getInstance(void);
    static void cleanUp(void);
    bool pushArguments(char *argv[]);
    bool printResult(void);

private:

    bool readOneArg(std::string arg);
    bool argToStack(const std::string& oneExpression);
    bool performOperations(int sign);
    bool meetSign(int sign);
    bool meetNumber(const std::string& numString);

    RPN(void);
    ~RPN(void);
    RPN& operator=(const RPN& rhs);
    RPN(const RPN& obj);

    static RPN *_calc;
    std::stack<int>  _numStack;

};

#endif
