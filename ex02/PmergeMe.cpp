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

void	merge(PmergeMe::intPairDeque& arrangedChain, PmergeMe::intPairDeque& mainChain, int left, int middle, int right)
{
	int	leftIdx = left;
	int	rightIdx = middle + 1;
	int	chainIdx = left;

	std::cout << "<left, middle, right>: " << left << ", " << middle << ", " <<right << std::endl;
	for (int i = left; i <= right; i++)
	{
		std::cout << i << ": " << mainChain[i].first << ", " << mainChain[i].second << std::endl;
	}
	std::cout << "\n\n" << std::endl;
	while (leftIdx <= middle && rightIdx <= right)
	{
		if (mainChain[leftIdx].first <= mainChain[rightIdx].first)
		{
			arrangedChain[chainIdx] = mainChain[leftIdx];
			leftIdx += 1;
		}
		else
		{
			arrangedChain[chainIdx] = mainChain[rightIdx];
			rightIdx += 1;
		}
		chainIdx += 1;
	}
	if (leftIdx > middle)
	{
		for (; rightIdx <= right; rightIdx++)
		{
			arrangedChain[chainIdx] = mainChain[rightIdx];
			chainIdx += 1;
		}
	}
	else
	{
		for (; leftIdx <= middle; leftIdx++)
		{
			arrangedChain[chainIdx] = mainChain[leftIdx];
			chainIdx += 1;
		}
	}
	int i = 0;
	for (PmergeMe::intPairDeque::iterator it = arrangedChain.begin(); it != arrangedChain.end(); it++)
	{
		std::cout << i << ": " << it->first << ", " << it->second << std::endl;
		i++;
	}
}

void mergeSort(PmergeMe::intPairDeque& arrangedChain, PmergeMe::intPairDeque& mainChain, int leftIdx, int rightIdx)
{
	if (leftIdx < rightIdx)
	{
		int middle = (leftIdx + rightIdx) / 2;
		mergeSort(arrangedChain, mainChain, leftIdx, middle);
		mergeSort(arrangedChain, mainChain, middle + 1, rightIdx);
		merge(arrangedChain, mainChain, leftIdx, middle, rightIdx);
	}
}

void PmergeMe::mergeInsertionSorting(void)
{
	//convert pair deque
	PmergeMe::intPairDeque	mainChain;
	int				straggler = -1;

	initPairDeque(_argsDeque, mainChain, straggler);
	//sort using merge insert
	PmergeMe::intPairDeque	arrangedMainChain(mainChain.size());
	mergeSort(arrangedMainChain, mainChain, 0, mainChain.size() - 1);
	// int i = 0;
	// for (PmergeMe::intPairDeque::iterator it = arrangedMainChain.begin(); it != arrangedMainChain.end(); it++)
	// {
	// 	i++;
	// 	std::cout << i << ": " << it->first << ", " << it->second << std::endl;
	// }
}

/* insertion sort + binary search*/
