#pragma once
#ifndef _PMERGEME_HPP_
#define _PMERGEME_HPP_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <deque>
#include <list>
#include "../Colors.hpp"

class PmergeMe
{

public:

	typedef	std::deque<std::pair<int, int> >	intPairDeque;
	typedef	std::list<std::pair<int, int> >		intPairList;

	static PmergeMe*	getInstance(void);
	static void			cleanUp(void);
	size_t				getRange(void);
	bool 				pushArguments(char *argv[]);
	void 				printRawArguments(void);
	void 				printArrangedArguments(void);
	void				mergeInsertionSortingDeque(void);
	void				mergeInsertionSortingList(void);

private:
 
	void	sortingPendingChainDeque(PmergeMe::intPairDeque& mainChain, int straggler);
	void	sortingPendingChainList(PmergeMe::intPairList& mainChain, int straggler);
	bool	readOneArg(std::string arg);
	bool	argToContainer(const std::string& oneExpression);
	bool	pushNumber(const std::string& numString);

	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe& operator=(const PmergeMe& rhs);
	PmergeMe(const PmergeMe& obj);

	static PmergeMe *_sorter;

	std::deque<int> _argsDeque;
	std::list<int> _argsList;
	

};

#endif
