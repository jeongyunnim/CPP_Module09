#include "RPN.hpp"

std::stack<int> RPN::_numStack;

bool	RPN::performOperations(int sign)
{
	long	result = 0;
	long	lhs;
	long	rhs;

	rhs = _numStack.top();
	_numStack.pop();
	lhs = _numStack.top();
	_numStack.pop();

	if (sign == '+')
		result = lhs + rhs;
	else if (sign == '-')
		result = lhs - rhs;
	else if (sign == '*')
		result = lhs * rhs;
	else
		result = lhs / rhs;
	/* print RPN processes */
	// std::cout << lhs << ' ' << static_cast<char>(sign) << ' ' << rhs <<  " = " << result << std::endl;
	if (result > INT32_MAX)
		return (false);
	_numStack.push(result);
	return (true);
}

static	int	printErrorInputReturnFalse(const std::string& input)
{
	std::cout << Colors::RedString("Error: invalid input: ") << input << std::endl;
	return (false);
}

bool	RPN::meetSign(int sign)
{
	if (_numStack.size() < 2)
	{
		std::cout << Colors::RedString("Error: expression pairs not matched") << std::endl;
		return (false);
	}
	else if (performOperations(sign) == false)
	{
		std::cout << Colors::RedString("Error: int overflow") << std::endl;
		return (false);	
	}
	return (true);
}

bool	RPN::meetNumber(const std::string& numString)
{
	int		iValue;

	for (std::string::const_iterator cit = numString.begin(); cit != numString.end(); cit++)
	{
		if (cit != numString.begin() && std::isdigit(*cit) == false)
			return (printErrorInputReturnFalse(numString));
	}
	iValue = std::atoi(numString.c_str());
	if (iValue < 0 || 10 < iValue)
	{
		std::cout << Colors::RedString("Error: argument range is {0 .. 10} ") << numString << std::endl;
		return (false);
	}
	_numStack.push(iValue);
	return (true);
}

bool RPN::argToStack(const std::string& oneExpression)
{

	if (oneExpression.empty() == true)
		return (printErrorInputReturnFalse(oneExpression));
	else if (oneExpression.size() == 1 && \
			(oneExpression[0] == '+' || oneExpression[0] == '-' || oneExpression[0] == '/' || oneExpression[0] == '*'))
	{
		if (meetSign(oneExpression[0]) == false)
			return (false);
	}
	else if ((oneExpression[0] != '+') && (oneExpression[0] != '-') && std::isdigit(oneExpression[0]) == false)
		return (printErrorInputReturnFalse(oneExpression));
	else
	{
		if (meetNumber(oneExpression) == false)
			return (false);
	}
	return (true);
}

bool RPN::readOneArg(std::string arg)
{
	std::stringstream argStream(arg);
	std::string oneExpression;

	while (1)
	{
		std::getline(argStream, oneExpression, ' ');
		if (argStream.eof() == false && argStream.fail() == true)
		{
			std::cout << Colors::RedString("Error: stream read error") << std::endl;
			return (false);
		}
		else if (argToStack(oneExpression) == false)
		{
			return (false);
		}
		if (argStream.eof() == true)
			return (true);
	}
}

bool RPN::pushArguments(char *argv[])
{
	for (int i = 1; argv[i] != NULL; i++)
	{
		if (readOneArg(argv[i]) == false)
			return (false);
	}
	return (true);
}

bool RPN::printResult(void)
{
	long				result = 0;

	result = _numStack.top();
	_numStack.pop();
	if (_numStack.empty() == false)
	{
		std::cout << Colors::RedString("Error: expression pairs not matched") <<std::endl;
		return (false);
	}
	std::cout << Colors::BoldBlueString("[Result]: ") << result << std::endl;
	return (true);
}
