#include "PmergeMe.hpp"

// init을 할 필요가 있나?
static void	initMainDeque(std::deque<int>& src, std::deque<Node>& mainChain, Node& straggler)
{
	Node temp;

	temp.content = -1;
	temp.pendingContent = -1;

	if (src.size() % 2 == 1)
		straggler.content = *src.rbegin();
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

static void binarySearchDeque(std::deque<Node>& mainChain, std::deque<Node>& arrangedChain, int index)
{
	int	left = 0;
	int	right = index;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (mainChain[mid].content == arrangedChain[index].pendingContent)
		{
			mainChain.insert(mainChain.begin() + mid, arrangedChain[index]);
			return ;
		}
		else if (mainChain[mid].content < arrangedChain[index].pendingContent)
			left = mid + 1;
		else
			right = mid - 1;
	}
	mainChain.insert(mainChain.begin() + left, arrangedChain[index]);
}

static void binarySearchDequeForOdd(std::deque<Node>& result, Node targetValue)
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

static void	pendPairDeque(std::deque<Node>& src, std::deque<Node>& target, Node& straggler)
{
	Node temp;

	temp.content = -1;
	temp.pendingContent = -1;

	if (src.size() % 2 == 1)
	{
		straggler = *(src.rbegin());
	}
	else
	{
		straggler.content = -1;
		straggler.pendingContent = -1;
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
		src.push_back(temp);
	}
}

std::deque<Node> PmergeMe::sortingMainChainRecursively(std::deque<Node>& mainChain, Node straggler)
{
	std::deque<Node>	subChain;
	std::deque<Node>	arrangedChain;
	Node				superStraggler = straggler;

	// 1인 경우 필요하지 않다면 패스
	if (mainChain.size() == 1)
	{
		return (mainChain);
	}
	else if (mainChain.size() == 2)
	{
		if (mainChain[0].content < mainChain[1].content)
		{
			std::cout << mainChain[0].content << " " << mainChain[1].content << std::endl;
			subChain.push_back(mainChain[0]);
			subChain.push_back(mainChain[1]);
		}
		else
		{
			std::cout << mainChain[1].content << " " << mainChain[0].content << std::endl;
			subChain.push_back(mainChain[1]);
			subChain.push_back(mainChain[0]);
		}
		return (subChain);
	}
	else
	{
		pendPairDeque(subChain, mainChain, straggler);

		arrangedChain = sortingMainChainRecursively(subChain, straggler);
		size_t 			i = 0;

		for (int jacobsthal = 0; i < arrangedChain.size(); i++ && jacobsthal++)
		{
			i = findJacobsthalNum(jacobsthal) - 1;
			if (i >= arrangedChain.size())
			{
				i = arrangedChain.size() - 1;
			}
			for (int j = i; j >= findJacobsthalNum(jacobsthal - 1); j--)
				binarySearchDeque(subChain, arrangedChain, j);
		}
		if (straggler.content >= 0)
			binarySearchDequeForOdd(subChain, superStraggler);
		return (subChain);
	}
}

void PmergeMe::mergeInsertionSortingDeque(void)
{
	std::deque<Node>	mainChain;
	Node				straggler;

	straggler.content = -1;
	straggler.pendingContent = -1;
	initMainDeque(mArgsDeque, mainChain, straggler);
	// init 필요 없음.
	mArgsDeque.clear();
	// std::sort(mainChain.begin(), mainChain.end());
	mainChain = sortingMainChainRecursively(mainChain, straggler);
	for (std::deque<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
	{
		mArgsDeque.push_back(it->content);
	}
}
