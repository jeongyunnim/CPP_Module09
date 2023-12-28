#include "PmergeMe.hpp"

static void	initMainList(std::list<int>& src, std::list<Node>& mainChain, Node& straggler)
{
	std::list<int>::iterator it = src.begin();
	Node temp;
	int first;
	int second;

	if (src.size() % 2 == 1)
		straggler.content = *src.rbegin();
	else
		straggler.content = -1;
	for (size_t i = 0; i < src.size() && i + 1 < src.size(); i += 2)
	{
		first = *it;
		it++;
		second = *it;
		it++;
		if (first > second)
		{
			temp.content = first;
			temp.pendingContent = second;
		}
		else
		{
			temp.content = second;
			temp.pendingContent = first;
		}
		mainChain.push_back(temp);
	}
}

static std::list<Node>::iterator ftAdvanced(std::list<Node>::iterator begin, std::list<Node>::iterator end, int index)
{
	int count = 0;
	for (; begin != end && count < index; begin++)
		count++;
	return (begin);
}

static size_t getLength(std::list<Node>::iterator begin, std::list<Node>::iterator end, int value)
{
	size_t	len = 0;
	bool	valueFlag;

	if (value >= 0)
		valueFlag = true;
	else
		valueFlag = false;
	while (begin != end)
	{
		if (valueFlag == true && begin->content == value)
			break ;
		len++;
		begin++;
	}
	return (len);
}

static void binarySearchList(std::list<Node>& mainChain, Node& targetValue)
{
	std::list<Node>::iterator	left = mainChain.begin();
	std::list<Node>::iterator	right = mainChain.end();
	size_t						len;
	Node						temp;
	int 						mid = -1;

	right--;
	temp.pendingContent = -1;
	while (getLength(mainChain.begin(), left, -1) <= getLength(mainChain.begin(), right, -1))
	{
		if (mid == -1)
			len = getLength(mainChain.begin(), mainChain.end(), targetValue.content);
		else
			len = getLength(left, right, -1);
		mid = getLength(mainChain.begin(), left, -1) + len / 2;
		if (ftAdvanced(mainChain.begin(), mainChain.end(), mid)->content == targetValue.pendingContent)
		{
			temp.content = targetValue.pendingContent;
			mainChain.insert(ftAdvanced(mainChain.begin(), mainChain.end(), mid), temp);
			return ;
		}
		else if (ftAdvanced(mainChain.begin(), mainChain.end(), mid)->content < targetValue.pendingContent)
			left = ftAdvanced(mainChain.begin(), mainChain.end(), mid + 1);
		else
		{
			if (mid == 0)
				break ;
			right = ftAdvanced(mainChain.begin(), mainChain.end(), mid - 1);
		}
	}
	temp.content = targetValue.pendingContent;
	mainChain.insert(left, temp);
}

static void binarySearchListForOdd(std::list<Node>& mainChain, Node& targetValue)
{
	std::list<Node>::iterator	left = mainChain.begin();
	std::list<Node>::iterator	right = mainChain.end();
	size_t						len;
	Node						temp;
	int 						mid = -1;

	right--;
	temp.pendingContent = -1;
	while (getLength(mainChain.begin(), left, -1) <= getLength(mainChain.begin(), right, -1))
	{
		if (mid == -1)
			len = getLength(mainChain.begin(), mainChain.end(), targetValue.content);
		else
			len = getLength(left, right, -1);
		mid = getLength(mainChain.begin(), left, -1) + len / 2;
		if (ftAdvanced(mainChain.begin(), mainChain.end(), mid)->content == targetValue.content)
		{
			temp.content = targetValue.content;
			mainChain.insert(ftAdvanced(mainChain.begin(), mainChain.end(), mid), temp);
			return ;
		}
		else if (ftAdvanced(mainChain.begin(), mainChain.end(), mid)->content < targetValue.content)
			left = ftAdvanced(mainChain.begin(), mainChain.end(), mid + 1);
		else
		{
			if (mid == 0)
				break ;
			right = ftAdvanced(mainChain.begin(), mainChain.end(), mid - 1);
		}
	}
	temp.content = targetValue.content;
	mainChain.insert(left, temp);
}

static void	separateMainChain(std::list<Node>& pendingChain, std::list<Node>& target, Node& straggler)
{
	Node temp;
	int	first;
	int second;

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
	std::list<Node>::iterator it = target.begin();
	for (size_t i = 0; i + 1 < target.size(); i += 2)
	{
		first = it->content;
		it++;
		second = it->content;
		it++;
		if (first > second)
		{
			temp.content = first;
			temp.pendingContent = second;
		}
		else
		{
			temp.content = second;
			temp.pendingContent = first;
		}
		pendingChain.push_back(temp);
	}
}

void PmergeMe::insertPendingChainList(std::list<Node>& mainChain)
{
	size_t				i = 0;
	std::list<Node>		result = mainChain;
	Node				temp;

	temp.pendingContent = -1;
	temp.content = mainChain.begin()->pendingContent;
	result.push_front(temp);
	for (int jacobsthalIndex = 1; i < mainChain.size(); i++ && jacobsthalIndex++)
	{
		i = findJacobsthalNum(jacobsthalIndex) - 1;
		if (i >= mainChain.size())
		{
			i = mainChain.size() - 1;
		}
		for (int j = i; j >= findJacobsthalNum(jacobsthalIndex - 1); j--)
			binarySearchList(result, *ftAdvanced(mainChain.begin(), mainChain.end(), j));
	}
	mainChain = result;
}

void PmergeMe::sortingMainChainRecursivelyList(std::list<Node>& mainChain, Node& superStraggler)
{
	std::list<Node>	separatedChain;
	Node			straggler;
	Node			temp;

	temp.pendingContent = -1;
	separateMainChain(separatedChain, mainChain, straggler);
	if (separatedChain.size() > 0)
	{
		sortingMainChainRecursivelyList(separatedChain, straggler);
	}
	else if (separatedChain.size() == 0)
	{
		if (separatedChain.size() == 0 && straggler.content >= 0)
		{
			temp.content = straggler.pendingContent;
			separatedChain.push_back(temp);
			temp.content = straggler.content;
			separatedChain.push_back(temp);
			if (superStraggler.content >= 0)
				binarySearchListForOdd(separatedChain, superStraggler);
			mainChain = separatedChain;
			return ;
		}
	}
	for (std::list<Node>::iterator separatedSequenceIt = separatedChain.begin(); separatedSequenceIt != separatedChain.end(); separatedSequenceIt++)
	{
		for (std::list<Node>::iterator originalSequenceIt = mainChain.begin(); originalSequenceIt != mainChain.end(); originalSequenceIt++)
		{
			if (separatedSequenceIt->content == originalSequenceIt->content)
			{
				separatedSequenceIt->pendingContent = originalSequenceIt->pendingContent;
				originalSequenceIt->content = -1;
				break ;
			}
		}
	}
	insertPendingChainList(separatedChain);
	if (superStraggler.content >= 0)
	{
		binarySearchListForOdd(separatedChain, superStraggler);
	}
	mainChain = separatedChain;
}

void PmergeMe::sortMainChainList(std::list<Node>& mainChain, Node& straggler)
{
	sortingMainChainRecursivelyList(mainChain, straggler);
	mArgsList.clear();
	for (std::list<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
	{
		mArgsList.push_back(it->content);
	}
}

void PmergeMe::mergeInsertionSortingList(void)
{
	std::list<Node>	mainChain;
	Node			straggler;
	std::list<int> test;

	if (mArgsList.size() <= 1)
	{
		return ;
	}
	straggler.content = -1;
	straggler.pendingContent = -1;
	initMainList(mArgsList, mainChain, straggler);
	test = mArgsList;
	sortMainChainList(mainChain, straggler);
}
