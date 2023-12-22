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

typedef struct Node
{
	int content;
	int pendingContent;
	int level;
} Node;

class PmergeMe
{

public:

	static PmergeMe*	getInstance(void);
	static void			cleanUp(void);
	size_t				getRange(void);
	bool 				pushArguments(char *argv[]);
	void 				printRawArguments(void);
	void 				printArrangedArguments(void);
	void				mergeInsertionSortingDeque(void);
	void				mergeInsertionSortingList(void);
	int					findJacobsthalNum(int index);

private:
 
	void	sortingPendingChainDeque(std::deque<Node>& mainChain, int straggler);
	// void	sortingPendingChainList(PmergeMe::intPairList& mainChain, int straggler);
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
