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
 
private:

	/* sort using deque */
	void	sortingMainChainRecursively(std::deque<Node>& mainChain, Node& superStraggler);
	void 	sortMainChain(std::deque<Node>& mainChain, Node& straggler);
	void	sortingPendingChainDeque(std::deque<Node>& mainChain, Node& straggler);
	void 	insertPendingChain(std::deque<Node>& mainChain);
	
	/* sort using list */
	void	sortingMainChainRecursivelyList(std::list<Node>& mainChain, Node& superStraggler);
	void	sortingPendingChainList(std::list<Node>& mainChain, Node& straggler);
	void 	sortMainChainList(std::list<Node>& mainChain, Node& straggler);
	void 	insertPendingChainList(std::list<Node>& mainChain);

	/* parsing */
	bool	readOneArg(std::string arg);
	bool	argToContainer(const std::string& oneExpression);
	bool	pushNumber(const std::string& numString);
	int		findJacobsthalNum(int index);

	/* Not use (orthodox canonical form) */
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
