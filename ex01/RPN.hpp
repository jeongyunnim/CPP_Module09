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

private:

    RPN(void);
    ~RPN(void);
    RPN& operator=(const RPN& rhs);
    RPN(const RPN& obj);

    static std::stack<std::string> _expressions;

};

#endif
