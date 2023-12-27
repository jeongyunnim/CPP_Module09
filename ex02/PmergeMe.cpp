#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {};
PmergeMe::~PmergeMe(void) {};

int	PmergeMe::findJacobsthalNum(int index)
{
	if (index == -1)
	{
		return (1);
	}
	return (mJacobsthalSequence[index]);
}

void PmergeMe::initJacobsthalSequence(void)
{
	bool	endFlag = false;
	int		jacobsthalIndex = 2;
	
	mJacobsthalSequence.push_back(1);
	mJacobsthalSequence.push_back(3);
	
	for (int jacobsthalNum = 0; endFlag == false; jacobsthalIndex++)
	{
		jacobsthalNum = mJacobsthalSequence[jacobsthalIndex - 1] + (2 * mJacobsthalSequence[jacobsthalIndex - 2]);
		mJacobsthalSequence.push_back(jacobsthalNum);
		if (jacobsthalNum > static_cast<int>(mArgsDeque.size()))
			endFlag = true;
	}

}

static size_t getLength(std::list<int>::iterator begin, std::list<int>::iterator end, int value)
{
	size_t	len = 0;
	bool	valueFlag = false;

	if (value >= 0)
		valueFlag = true;
	for (; begin != end; begin++)
	{
		if (valueFlag == true && *begin == value)
			break ;
		len++;
	}
	return (len);
}

void	PmergeMe::sortingPendingChainList(PmergeMe::intPairList& mainChain, int straggler)
{
	PmergeMe::intPairList::iterator it = mainChain.begin();
	int	 			jacobsthal = 1;

	if (mainChain.size() == 0)
		return ;
	for (; it != mainChain.end(); it++)
		_argsList.push_back(it->first);
	it = mainChain.begin();
	_argsList.push_front(it->second);
	for (size_t i = 0; i < mainChain.size(); i++ && jacobsthal++)
	{
		i = findJacobsthalNum(jacobsthal) - 1;
		if (i >= mainChain.size())
			i = mainChain.size() - 1;
		for (int j = i; j >= findJacobsthalNum(jacobsthal - 1); j--)
			binarySearchList(_argsList, *ftAdvancedForPair(mainChain.begin(), mainChain.end(), j));
	}
	if (straggler >= 0)
		binarySearchListForOdd(_argsList, straggler);
}

void PmergeMe::mergeInsertionSortingList(void)
{
	PmergeMe::intPairList	mainChain;
	int						straggler = -1;

	initPairList(_argsList, mainChain, straggler);
	mainChain.sort();
	_argsList.clear();
	sortingPendingChainList(mainChain, straggler);
}
