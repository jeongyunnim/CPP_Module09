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

/* FJ sort*/
static void	initPairDeque(std::deque<int>& src, std::deque<std::pair<int , int> >& mainChain, int& straggler)
{
	if (src.size() % 2 == 1)
		straggler = *src.rbegin();
	for (std::deque<int>::iterator it = src.begin(); it + 1 != src.end() && it != src.end(); it += 2)
	{
		if (*it > *(it + 1))
			mainChain.push_back(std::pair<int, int>(*it, *(it + 1)));
		else
			mainChain.push_back(std::pair<int, int>(*(it + 1), *it));
	}
}

int	findJacobsthalNum(int index)
{
	if (index == 0)
		return (1);
	else if (index == 1)
		return (3);
	return (findJacobsthalNum(index - 1) + 2 * findJacobsthalNum(index - 2));
}

static void binarySearch(std::deque<int>& result, std::pair<int,int>& targetValue)
{
	int	left = 0;
	int	right = 0;

	for (std::deque<int>::iterator it = result.begin(); it != result.end(); it++)
	{
		if (*it == targetValue.first)
			break ;
		right += 1;
	}
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (result[mid] == targetValue.second)
		{
			result.insert(result.begin() + mid, targetValue.second);
			return ;
		}
		else if (result[mid] < targetValue.second)
			left = mid + 1;
		else
			right = mid - 1;
	}
	result.insert(result.begin() + left, targetValue.second);

}

static void binarySearchForOdd(std::deque<int>& result, int& targetValue)
{
	int	left = 0;
	int	right = result.size() - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (result[mid] == targetValue)
		{
			result.insert(result.begin() + mid, targetValue);
			return ;
		}
		else if (result[mid] < targetValue)
			left = mid + 1;
		else
			right = mid - 1;
	}
	result.insert(result.begin() + left, targetValue);
}

void	PmergeMe::sortingPendingchain(PmergeMe::intPairDeque& mainChain, int straggler)
{
	std::deque<int> result;
	size_t 			i = 0;
	int	 			jacobsthal = 1;

	for (PmergeMe::intPairDeque::iterator it = mainChain.begin(); it != mainChain.end(); it++)
	{
		result.push_back(it->first);
	}
	result.push_front(mainChain[i].second);
	while (i < mainChain.size())
	{
		/* 다음 야스콥탈 수를 가져와야 함. 그 뒤에 전 야스콥탈 수보다 적게 가져가야 함. */
		i = findJacobsthalNum(jacobsthal) - 1;
		if (i >= mainChain.size())
			i = mainChain.size() - 1;
		for (int j = i; j >= findJacobsthalNum(jacobsthal - 1); j--)
		{
			binarySearch(result, mainChain[j]);
		}
		jacobsthal += 1;
		i++;
	}
	if (straggler >= 0)
		binarySearchForOdd(result, straggler);
	_argsDeque = result;
}

void PmergeMe::mergeInsertionSorting(void)
{
	//convert pair deque
	PmergeMe::intPairDeque	mainChain;
	int				straggler = -1;

	initPairDeque(_argsDeque, mainChain, straggler);
	std::sort(mainChain.begin(), mainChain.end());
	//sort pendingchan.
	sortingPendingchain(mainChain, straggler);

	for (std::deque<int>::iterator it = _argsDeque.begin(); it != _argsDeque.end(); it++)
	{
		std::cout << *it << ' ';
	}
}

/* insertion sort + binary search*/
