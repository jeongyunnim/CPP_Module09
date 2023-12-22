#include "PmergeMe.hpp"

PmergeMe *PmergeMe::_sorter = NULL;

size_t	PmergeMe::getRange(void)
{
	return (_argsDeque.size());
}

PmergeMe*	PmergeMe::getInstance(void)
{
	if(_sorter == NULL)
		_sorter = new PmergeMe();
	return (_sorter);
}

void		PmergeMe::cleanUp(void)
{
	if (_sorter != NULL)
		delete _sorter;
}