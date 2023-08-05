#include "RPN.hpp"

std::stack<std::string> RPN::_expressions;

static bool isValidExpression(const std::string& oneExpression)
{
	int		iValue;

	if (oneExpression.empty() == true)
		return (false);
	else if (oneExpression.size() == 1 && (oneExpression[0] == '+' || oneExpression[0] == '-' || oneExpression[0] == '/' || oneExpression[0] == '*'))
		return (true);
	else if ((oneExpression[0] != '+') && std::isdigit(oneExpression[0]) == false)
		return (false);
	for (std::string::const_iterator cit = oneExpression.begin(); cit != oneExpression.end(); cit++)
	{
		if (cit != oneExpression.begin() && std::isdigit(*cit) == false)
			return (false);
	}
	iValue = std::atoi(oneExpression.c_str());
	if (iValue < 0 || 10 < iValue)
		return (false);
	return (true);
}

bool RPN::readOneArg(std::string arg)
{
	std::stringstream argStream(arg);
	std::string oneExpression;

	std::cout << "check one arg: " << arg << std::endl;
	while (1)
	{
		std::getline(argStream, oneExpression, ' ');
		if (argStream.eof() == false && argStream.fail() == true)
		{
			std::cout << Colors::RedString("Error: stream read error") << std::endl;
			return (false);
		}
		else if (isValidExpression(oneExpression) == false)
		{
			std::cout << Colors::RedString("Error: invalid input: ") << oneExpression << std::endl;
			return (false);
		}
		else
		{
			_expressions.push(oneExpression);
		}
		if (argStream.eof() == true)
			return (true);
	}
}

template <typename T>
static void printStack(std::stack<T>& stack)
{
	std::stack<T> s(stack);

	std::cout << Colors::Blue << "[print stack]" << Colors::Reset << std::endl;
	while (s.empty() == 0)
	{
		std::cout << "|" << std::left << std::setw(3) << s.top() << '|' << std::endl;
		s.pop();
	}
}

bool RPN::pushArguments(char *argv[])
{
	for (int i = 1; argv[i] != NULL; i++)
	{
		if (readOneArg(argv[i]) == false)
			return (false);
	}
	printStack(_expressions);
	/*
	1. 인자 체크 밖에서.
	2. 유효한 숫자인지 체크
	3. 유효한 기호인지 체크
	4. 인자가 잘 들어왔는지 체크 (인자 입력 순서)
	5. 각 연산 수행.
	*/
	return (true);
}
