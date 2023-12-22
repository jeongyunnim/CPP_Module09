#include "PmergeMe.hpp"

// init을 할 필요가 있나?
static void	initMainDeque(std::deque<int>& src, std::deque<Node>& mainChain, int& straggler)
{
	Node temp;

	temp.content = -1;
	temp.pendingContent = -1;
	temp.level = 0;

	if (src.size() % 2 == 1)
		straggler = *src.rbegin();
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


static void binarySearchDeque(std::deque<int>& result, Node& targetValue)
{
	int	left = 0;
	int	right = 0;

	for (std::deque<int>::iterator it = result.begin(); it != result.end(); it++)
	{
		if (*it == targetValue.content)
			break ;
		right += 1;
	}
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (result[mid] == targetValue.pendingContent)
		{
			result.insert(result.begin() + mid, targetValue.pendingContent);
			return ;
		}
		else if (result[mid] < targetValue.pendingContent)
			left = mid + 1;
		else
			right = mid - 1;
	}
	result.insert(result.begin() + left, targetValue.pendingContent);

}

static void binarySearchDequeForOdd(std::deque<int>& result, int& targetValue)
{
	int	left = 0;
	int	right = result.size() - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (result[mid] == targetValue)
		{
			result.insert(result.begin() + mid, targetValue);
			return ;
		}
		else if (result[mid] < targetValue)
			left = mid + 1;
		else
			right = mid - 1;
	}
	result.insert(result.begin() + left, targetValue);
}

void	PmergeMe::sortingPendingChainDeque(std::deque<Node>& mainChain, int straggler)
{
	size_t 			i = 0;

	for (std::deque<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		_argsDeque.push_back(it->content);
	if (mainChain.size() == 0)
		return ;
	_argsDeque.push_front((mainChain[i]).pendingContent);
	for (int jacobsthal = 1; i < mainChain.size(); i++ && jacobsthal++)
	{
		i = findJacobsthalNum(jacobsthal) - 1;
		if (i >= mainChain.size())
			i = mainChain.size() - 1;
		for (int j = i; j >= findJacobsthalNum(jacobsthal - 1); j--)
			binarySearchDeque(_argsDeque, mainChain[j]);
	}
	if (straggler >= 0)
		binarySearchDequeForOdd(_argsDeque, straggler);
}

void sortingMainChainRecursively(std::deque<Node> mainChain, int straggler)
{
	// content를 비교해가면서 싹 잘라야 함.
	// 1개인 경우 생길 수가 없기는 함.
	if (mainChain.size() < 3)
	{
		//정렬하고 리턴
		return ;
	}
	// if (정렬이 안되어있다면) -> 짤라 계속.
}

void PmergeMe::mergeInsertionSortingDeque(void)
{
	std::deque<Node> mainChain;
	int	straggler = -1;

	// init을 할 필요가 있나? size 0~1일 때 예외처리 해야 함.
	initMainDeque(_argsDeque, mainChain, straggler);
	// init 필요 없음.
	_argsDeque.clear();
	// std::sort(mainChain.begin(), mainChain.end());
	sortingPendingChainDeque(mainChain, straggler);
}
