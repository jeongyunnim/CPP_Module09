#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {};
PmergeMe::~PmergeMe(void) {};

int	PmergeMe::findJacobsthalNum(int index)
{
	return (mJacobsthalSequence[index]);
}

void PmergeMe::initJacobsthalSequence(void)
{
	bool	endFlag = false;
	int		jacobsthalIndex = 2;
	
	mJacobsthalSequence.push_back(3);
	mJacobsthalSequence.push_back(5);
	
	for (int jacobsthalNum = 0; endFlag == false;)
	{
		jacobsthalNum = mJacobsthalSequence[jacobsthalIndex - 1] + (2 * mJacobsthalSequence[jacobsthalIndex - 2]);
		mJacobsthalSequence.push_back(jacobsthalNum);

		if (jacobsthalNum > static_cast<int>(mArgsDeque.size()))
			endFlag = true;
	}
}

/* Using List */

// static void	initPairList(std::list<int>& src, std::list<std::pair<int , int> >& mainChain, int& straggler)
// {
// 	std::list<int>::iterator it = src.begin();
// 	int first;
// 	int second;
	
// 	if (src.size() % 2 == 1)
// 		straggler = *src.rbegin();
// 	for (size_t i = 0; i < src.size() && i + 1 < src.size(); i += 2)
// 	{
// 		first = *it;
// 		it++;
// 		second = *it;
// 		it++;
// 		if (first > second)
// 			mainChain.push_back(std::pair<int, int>(first, second));
// 		else
// 			mainChain.push_back(std::pair<int, int>(second, first));
// 	}
// }

// static std::list<int>::iterator ftAdvanced(std::list<int>::iterator begin, std::list<int>::iterator end, int index)
// {
// 	int count = 0;
// 	for (; begin != end && count < index; begin++)
// 		count++;
// 	return (begin);
// }

// static size_t getLength(std::list<int>::iterator begin, std::list<int>::iterator end, int value)
// {
// 	size_t	len = 0;
// 	bool	valueFlag = false;

// 	if (value >= 0)
// 		valueFlag = true;
// 	for (; begin != end; begin++)
// 	{
// 		if (valueFlag == true && *begin == value)
// 			break ;
// 		len++;
// 	}
// 	return (len);
// }

// static void binarySearchList(std::list<int>& result, std::pair<int,int>& targetValue)
// {
// 	std::list<int>::iterator	left = result.begin();
// 	std::list<int>::iterator	right = result.end();
// 	size_t						len;
// 	int 						mid = -1;

// 	right--;
// 	while (getLength(result.begin(), left, -1) <= getLength(result.begin(), right, -1))
// 	{
// 		if (mid == -1)
// 			len = getLength(result.begin(), result.end(), targetValue.first);
// 		else
// 			len = getLength(left, right, -1);
// 		mid = getLength(result.begin(), left, -1) + len / 2;
// 		if (*ftAdvanced(result.begin(), result.end(), mid) == targetValue.second)
// 		{
// 			result.insert(ftAdvanced(result.begin(), result.end(), mid), targetValue.second);
// 			return ;
// 		}
// 		else if (*ftAdvanced(result.begin(), result.end(), mid) < targetValue.second)
// 			left = ftAdvanced(result.begin(), result.end(), mid + 1);
// 		else
// 		{
// 			if (mid == 0)
// 				break ;
// 			right = ftAdvanced(result.begin(), result.end(), mid - 1);
// 		}
// 	}
// 	result.insert(left, targetValue.second);

// }

// static void binarySearchListForOdd(std::list<int>& result, int& targetValue)
// {
// 	std::list<int>::iterator	left = result.begin();
// 	std::list<int>::iterator	right = result.end();
// 	right--;
// 	int 						mid = -1;
// 	int 						len = 0;

// 	while (getLength(result.begin(), left, -1) <= getLength(result.begin(), right, -1))
// 	{
// 		if (mid == -1)
// 			len = getLength(result.begin(), result.end(), targetValue);
// 		else
// 			len = getLength(left, right, -1);
// 		mid = getLength(result.begin(), left, -1) + len / 2;
// 		if (*ftAdvanced(result.begin(), result.end(), mid) == targetValue)
// 		{
// 			result.insert(ftAdvanced(result.begin(), result.end(), mid), targetValue);
// 			return ;
// 		}
// 		else if (*ftAdvanced(result.begin(), result.end(), mid) < targetValue)
// 			left = ftAdvanced(result.begin(), result.end(), mid + 1);
// 		else
// 		{
// 			if (mid == 0)
// 				break ;
// 			right = ftAdvanced(result.begin(), result.end(), mid - 1);
// 		}
// 	}
// 	result.insert(left, targetValue);
// }

// static std::list<std::pair<int, int> >::iterator ftAdvancedForPair(std::list<std::pair<int , int> >::iterator begin, std::list<std::pair<int , int> >::iterator end, int index)
// {
// 	int count = 0;
// 	for (; begin != end && count != index; begin++)
// 		count++;
// 	return (begin);
// }

// void	PmergeMe::sortingPendingChainList(PmergeMe::intPairList& mainChain, int straggler)
// {
// 	PmergeMe::intPairList::iterator it = mainChain.begin();
// 	int	 			jacobsthal = 1;

// 	if (mainChain.size() == 0)
// 		return ;
// 	for (; it != mainChain.end(); it++)
// 		_argsList.push_back(it->first);
// 	it = mainChain.begin();
// 	_argsList.push_front(it->second);
// 	for (size_t i = 0; i < mainChain.size(); i++ && jacobsthal++)
// 	{
// 		i = findJacobsthalNum(jacobsthal) - 1;
// 		if (i >= mainChain.size())
// 			i = mainChain.size() - 1;
// 		for (int j = i; j >= findJacobsthalNum(jacobsthal - 1); j--)
// 			binarySearchList(_argsList, *ftAdvancedForPair(mainChain.begin(), mainChain.end(), j));
// 	}
// 	if (straggler >= 0)
// 		binarySearchListForOdd(_argsList, straggler);
// }

// void PmergeMe::mergeInsertionSortingList(void)
// {
// 	PmergeMe::intPairList	mainChain;
// 	int						straggler = -1;

// 	initPairList(_argsList, mainChain, straggler);
// 	mainChain.sort();
// 	_argsList.clear();
// 	sortingPendingChainList(mainChain, straggler);
// }
