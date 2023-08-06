#include "PmergeMe.hpp"

std::deque<int> PmergeMe::_argsDeque;
std::list<int> PmergeMe::_argsList;

/* argument parsing */
void PmergeMe::printArguments(void)
{
	std::cout << Colors::BoldMagentaString("[original sequence]") << std::endl;
	for (std::deque<int>::const_iterator cit = _argsDeque.begin(); cit != _argsDeque.end(); cit++)
	{
		std::cout << *cit << ' ';
	}
	std::cout << std::endl;
}

static	int	printErrorInputReturnFalse(const std::string& input)
{
	std::cout << Colors::RedString("Error: invalid input: ") << input << std::endl;
	return (false);
}

bool	PmergeMe::pushNumber(const std::string& numString)
{
	long	lValue;

	for (std::string::const_iterator cit = numString.begin(); cit != numString.end(); cit++)
	{
		if (cit != numString.begin() && std::isdigit(*cit) == false)
			return (printErrorInputReturnFalse(numString));
	}
	lValue = std::atol(numString.c_str());
	if (lValue < 0 || INT32_MAX < lValue)
	{
		std::cout << Colors::RedString("Error: argument range is {0 .. INT_MAX} ") << numString << std::endl;
		return (false);
	}
	_argsDeque.push_back(lValue);
	_argsList.push_back(lValue);
	return (true);
}

bool PmergeMe::argToContainer(const std::string& oneExpression)
{
	if (oneExpression.empty() == true)
		return (printErrorInputReturnFalse(oneExpression));
	else if ((oneExpression[0] != '+') && (oneExpression[0] != '-') && std::isdigit(oneExpression[0]) == false)
		return (printErrorInputReturnFalse(oneExpression));
	else
	{
		if (pushNumber(oneExpression) == false)
			return (false);
	}
	return (true);
}

bool PmergeMe::readOneArg(std::string arg)
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
		else if (argToContainer(oneExpression) == false)
			return (false);
		if (argStream.eof() == true)
			return (true);
	}
}

bool PmergeMe::pushArguments(char *argv[])
{
	for (int i = 1; argv[i] != NULL; i++)
	{
		if (readOneArg(argv[i]) == false)
			return (false);
	}
	return (true);
}

/* merge sort*/

size_t mergeSorting(std::deque<int>& target) // reference로 주고 싶은데 어떻게 할지 일단 고민 스택에 쌓이는 거라서 참조로 넘겨줘도 되는지 궁금
{
	std::deque<int> a(target.size() / 2);
	std::deque<int> b(target.size() - a.size());
	int				range = 0;

	for (std::deque<int>::iterator it = target.begin(); it != target.end(); it++)
	{
		if (range < target.size() / 2)
			a.push_back(*it);
		else
			b.push_back(*it);
		range++;
	}
	/* 
	1. 분할
	2. 최소단위에 이르르면 두 놈을 비교하여 insert
	3. 병합 (바이너리 서치로 찾아서 삽입 정렬)
	*/
	size_t	range = target.size();

	if (range <= 2)
	{

	}

	mergeSorting(range / 2);
}

/* insertion sort + binary search*/
