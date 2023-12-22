#include "PmergeMe.hpp"

PmergeMe *PmergeMe::mSorter = NULL;

size_t	PmergeMe::getRange(void)
{
	return (mArgsDeque.size());
}

PmergeMe*	PmergeMe::getInstance(void)
{
	if(mSorter == NULL)
		mSorter = new PmergeMe();
	return (mSorter);
}

void		PmergeMe::cleanUp(void)
{
	if (mSorter != NULL)
		delete mSorter;
}