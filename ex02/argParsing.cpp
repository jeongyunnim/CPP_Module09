#include "PmergeMe.hpp"

void PmergeMe::printRawArguments(void)
{
	std::cout << Colors::BoldMagentaString("[original sequence]") << std::endl;
	for (std::deque<int>::const_iterator cit = mArgsDeque.begin(); cit != mArgsDeque.end(); cit++)
	{
		std::cout << *cit << ' ';
	}
	std::cout << std::endl;
}

void PmergeMe::printArrangedArguments(void)
{
	int temp = *mArgsDeque.begin();
	std::cout << Colors::BoldMagentaString("[sorted sequence]") << std::endl;
	std::cout << Colors::BlueString("[deque] ");
	for (std::deque<int>::const_iterator cit = mArgsDeque.begin(); cit != mArgsDeque.end(); cit++)
	{
		if (temp > *cit)
		{
			std::cout << Colors::RedString("Error: not arranged ") << *cit << std::endl;
			// return ;
		}
		temp = *cit;
		std::cout << *cit << ' ';
	}
	std::cout << std::endl;
	
	// temp = *mArgsList.begin();
	// std::cout << Colors::BlueString("[list]  ");
	// for (std::list<int>::const_iterator cit = mArgsList.begin(); cit != mArgsList.end(); cit++)
	// {
	// 	if (temp > *cit)
	// 	{
	// 		std::cout << Colors::RedString("Error: not arranged ") << *cit << std::endl;
	// 		// return ;
	// 	}
	// 	temp = *cit;
	// 	std::cout << *cit << ' ';
	// }
	// std::cout << std::endl;
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
	mArgsDeque.push_back(lValue);
	mArgsList.push_back(lValue);
	return (true);
}

bool PmergeMe::argToContainer(const std::string& oneExpression)
{
	if (oneExpression.empty() == true)
		return (true);
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
