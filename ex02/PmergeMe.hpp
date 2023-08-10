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

	static size_t	getRange(void);
	static bool 	pushArguments(char *argv[]);
	static void 	printRawArguments(void);
	static void 	printArrangedArguments(void);
	static void		mergeInsertionSortingDeque(void);
	static void		mergeInsertionSortingList(void);

private:

	static void	sortingPendingChainDeque(PmergeMe::intPairDeque& mainChain, int straggler);
	static void	sortingPendingChainList(PmergeMe::intPairList& mainChain, int straggler);
	static bool	readOneArg(std::string arg);
	static bool	argToContainer(const std::string& oneExpression);
	static bool	pushNumber(const std::string& numString);

	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe& operator=(const PmergeMe& rhs);
	PmergeMe(const PmergeMe& obj);

	static std::deque<int> _argsDeque;
	static std::list<int> _argsList;
	

};

#endif
