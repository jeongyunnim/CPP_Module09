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
	void				initJacobsthalSequence(void);
	void				sortingMainChainRecursively(std::deque<Node>& mainChain, Node straggler);
 
private:

	void 	sortMainChain(std::deque<Node>& mainChain, Node& straggler);
	void	sortingPendingChainDeque(std::deque<Node>& mainChain, Node& straggler);
	// void	sortingPendingChainList(PmergeMe::intPairList& mainChain, Node& straggler);
	bool	readOneArg(std::string arg);
	bool	argToContainer(const std::string& oneExpression);
	bool	pushNumber(const std::string& numString);
	int		findJacobsthalNum(int index);
	void 	insertPendingChain(std::deque<Node>& mainChain, Node& straggler);

	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe& operator=(const PmergeMe& rhs);
	PmergeMe(const PmergeMe& obj);

	static PmergeMe *mSorter;

	std::deque<int> mArgsDeque;
	std::list<int>	mArgsList;
	std::deque<int> mJacobsthalSequence;

};

#endif
