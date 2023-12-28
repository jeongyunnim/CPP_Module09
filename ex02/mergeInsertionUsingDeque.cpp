#include "PmergeMe.hpp"

static void	initMainDeque(std::deque<int>& src, std::deque<Node>& mainChain, Node& straggler)
{
	Node temp;

	temp.content = -1;
	temp.pendingContent = -1;

	if (src.size() % 2 == 1)
	{
		straggler.content = *src.rbegin();
	}
	else 
	{
		straggler.content = -1;
	}
	for (std::deque<int>::iterator it = src.begin(); it + 1 != src.end() && it != src.end(); it += 2)
	{
		if (*it > *(it + 1))
		{
			temp.content = *it;
			temp.pendingContent = *(it + 1);
		}
		else
		{
			temp.content = *(it + 1);
			temp.pendingContent = *it;
		}
		mainChain.push_back(temp);
	}
}

static void binarySearchDeque(std::deque<Node>& mainChain, Node& targetValue)
{
	int	left = 0;
	int	right = 0;
	Node temp;

	temp.content = targetValue.pendingContent;
	temp.pendingContent = -1;
	for (std::deque<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
	{
		if (it->content == targetValue.content)
			break ;
		right++;
	}
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (mainChain[mid].content == targetValue.pendingContent)
		{
			mainChain.insert(mainChain.begin() + mid, temp);
			return ;
		}
		else if (mainChain[mid].content < targetValue.pendingContent)
			left = mid + 1;
		else
			right = mid - 1;
	}
	mainChain.insert(mainChain.begin() + left, temp);
}

static void binarySearchDequeForOdd(std::deque<Node>& result, Node& targetValue)
{
	int	left = 0;
	int	right = result.size() - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (result[mid].content == targetValue.content)
		{
			result.insert(result.begin() + mid, targetValue);
			return ;
		}
		else if (result[mid].content < targetValue.content)
			left = mid + 1;
		else
			right = mid - 1;
	}
	result.insert(result.begin() + left, targetValue);
}

static void	separateMainChain(std::deque<Node>& pendingChain, std::deque<Node>& target, Node& straggler)
{
	Node temp;

	temp.content = -1;
	temp.pendingContent = -1;

	if (target.size() % 2 == 1)
	{
		straggler.content = (target.rbegin())->content;
		straggler.pendingContent = (target.rbegin())->pendingContent;
	}
	else
	{
		straggler.content = -1;
		straggler.pendingContent = -1;
	}
	if (target.size() <= 1)
	{
		return ;
	}
	for (std::deque<Node>::iterator it = target.begin(); it + 1 != target.end() && it != target.end(); it += 2)
	{
		if (it->content > (it + 1)->content)
		{
			temp.content = it->content;
			temp.pendingContent = (it + 1)->content;
		}
		else
		{
			temp.content = (it + 1)->content;
			temp.pendingContent = it->content;
		}
		pendingChain.push_back(temp);
	}
}

void PmergeMe::insertPendingChain(std::deque<Node>& mainChain)
{
	size_t				i = 0;
	std::deque<Node>	result = mainChain;
	Node				temp;

	temp.pendingContent = -1;
	if (mainChain.size() == 2)
	{
		temp.content = mainChain[0].pendingContent;
		result.push_front(temp);
		binarySearchDeque(result, mainChain[1]);
	}
	else
	{
		temp.content = mainChain[0].pendingContent;
		result.push_front(temp);
		for (int jacobsthalIndex = 1; i < mainChain.size(); i++ && jacobsthalIndex++)
		{
			i = findJacobsthalNum(jacobsthalIndex) - 1;
			if (i >= mainChain.size())
			{
				i = mainChain.size() - 1;
			}
			for (int j = i; j >= findJacobsthalNum(jacobsthalIndex - 1); j--)
				binarySearchDeque(result, mainChain[j]);
		}
	}
	mainChain = result;
}

void PmergeMe::sortingMainChainRecursively(std::deque<Node>& mainChain, Node& superStraggler)
{
	std::deque<Node>	separatedChain;
	Node				straggler;

	//main chain to M--P chain(1/2 size) + init straggler
	separateMainChain(separatedChain, mainChain, straggler);
	if (separatedChain.size() > 0)
	{
		sortingMainChainRecursively(separatedChain, straggler);
	}
	else if (separatedChain.size() == 0)
	{
		Node temp;

		temp.pendingContent = -1;
		if (separatedChain.size() == 0 && straggler.content >= 0)
		{
			temp.content = straggler.pendingContent;
			separatedChain.push_back(temp);
			temp.content = straggler.content;
			separatedChain.push_back(temp);
			if (superStraggler.content >= 0)
				binarySearchDequeForOdd(separatedChain, superStraggler);
			mainChain = separatedChain;
			return ;
		}
	}

	for (std::deque<Node>::iterator separatedSequenceIt = separatedChain.begin(); separatedSequenceIt != separatedChain.end(); separatedSequenceIt++)
	{
		for (std::deque<Node>::iterator originalSequenceIt = mainChain.begin(); originalSequenceIt != mainChain.end(); originalSequenceIt++)
		{
			if (separatedSequenceIt->content == originalSequenceIt->content)
			{
				separatedSequenceIt->pendingContent = originalSequenceIt->pendingContent;
				originalSequenceIt->content = -1;
				break ;
			}
		}
	}
	insertPendingChain(separatedChain);
	if (superStraggler.content >= 0)
		binarySearchDequeForOdd(separatedChain, superStraggler);
	mainChain = separatedChain;
}

void PmergeMe::sortMainChain(std::deque<Node>& mainChain, Node& straggler)
{
	sortingMainChainRecursively(mainChain, straggler);
}

void PmergeMe::mergeInsertionSortingDeque(void)
{
	std::deque<Node>	mainChain;
	Node				straggler;
	std::deque<int> test;

	if (mArgsDeque.size() <= 1)
	{
		return ;
	}
	straggler.content = -1;
	straggler.pendingContent = -1;
	initMainDeque(mArgsDeque, mainChain, straggler);
	
	test = mArgsDeque;
	mArgsDeque.clear();
	sortMainChain(mainChain, straggler);
	for (std::deque<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
	{
		mArgsDeque.push_back(it->content);
	}
}
