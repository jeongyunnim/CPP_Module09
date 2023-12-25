#include "PmergeMe.hpp"

// init을 할 필요가 있나?
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
	Node temp;

	temp.content = targetValue.content;
	temp.pendingContent = -1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (result[mid].content == targetValue.content)
		{
			result.insert(result.begin() + mid, temp);
			return ;
		}
		else if (result[mid].content < targetValue.content)
			left = mid + 1;
		else
			right = mid - 1;
	}
	result.insert(result.begin() + left, temp);
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

void PmergeMe::insertPendingChain(std::deque<Node>& mainChain, Node& straggler)
{
	size_t				i = 0;
	std::deque<Node>	result = mainChain;
	Node				temp;

	temp.pendingContent = -1;

	std::cout << "original sequence: ";
	for (std::deque<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
	{
		std::cout << it->content << " ";
	}
	std::cout << std::endl;
	std::cout << "original subsequn: ";
	for (std::deque<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
	{
		std::cout << it->pendingContent << " ";
	}
	std::cout << std::endl;
	std::cout << "  ㄴstraggler: " << straggler.content << std::endl;
	std::cout << "  ㄴstraggler: " << straggler.pendingContent << std::endl;

	if (mainChain.size() == 0 && straggler.content >= 0)
	{
		temp.content = straggler.pendingContent;
		mainChain.push_back(temp);
		temp.content = straggler.content;
		mainChain.push_back(temp);
		std::cout << "arranged sequence: ";
		for (std::deque<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
		{
			std::cout << it->content << " ";
		}
		std::cout << std::endl;
		return ;
	}
	else if (mainChain.size() == 2)
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
	if (straggler.content >= 0)
		binarySearchDequeForOdd(result, straggler);

	std::cout << "arranged sequence: ";
	for (std::deque<Node>::iterator it = result.begin(); it != result.end(); it++)
	{
		std::cout << it->content << " ";
	}
	std::cout << std::endl;
	mainChain = result;
}

void PmergeMe::sortingMainChainRecursively(std::deque<Node>& mainChain, Node superStraggler)
{
	std::deque<Node>	separatedChain;
	Node				straggler;
	static size_t		sequenceSize;
	/*
		1. 재귀로 나눈다.
		2. 처음으로 풀릴 때 정렬이 된 상태로 반환한다.
		3. 각각 배열을 반환 받으면서 정렬이 된다.
			3-1. 반환받은 배열의 순서대로 상위 배열이 정렬이 되어야 함.
		4. 호출한 상태의 배열을 반환하게 된다.
	*/

	if (sequenceSize == 0)
	{
		std::cout << "sequence size initialized with: " << mainChain.size() << "\n" << std::endl;
		sequenceSize = mainChain.size();
	}
	if (mainChain.size() == 0 && straggler.content >= 0)
	{
		std::cout << "마지막 한 짝" << std::endl;
		insertPendingChain(separatedChain, superStraggler);
		mainChain = separatedChain;
		return ;
	}
	else if (mainChain.size() > 0 && mainChain[0].pendingContent == -1)
	{
		return ;
	}
	// else if (mainChain.size() <= 2)
	// {
	// 	std::cout << Colors::MagentaString("2개 아래라 return") << std::endl;
	// 	insertPendingChain(mainChain, superStraggler);
	// 	return ;
	// }

	//main chain to M--P chain(1/2 size) + init straggler
	separateMainChain(separatedChain, mainChain, straggler);
	
	if (separatedChain.size() > 0)
	{
		sortingMainChainRecursively(separatedChain, superStraggler);
	}
	for (std::deque<Node>::iterator separatedSequenceIt = separatedChain.begin(); separatedSequenceIt != separatedChain.end(); separatedSequenceIt++)
	{
		std::cout << separatedSequenceIt->content << " changed ";
		for (std::deque<Node>::iterator originalSequenceIt = mainChain.begin(); originalSequenceIt != mainChain.end(); originalSequenceIt++)
		{
			if (separatedSequenceIt->content == originalSequenceIt->content)
			{
				std::cout << separatedSequenceIt->pendingContent << " -> " << originalSequenceIt->pendingContent << std::endl;
				separatedSequenceIt->pendingContent = originalSequenceIt->pendingContent;
				originalSequenceIt->content = -1;
				break ;
			}
		}
	}
	std::cout << Colors::BoldBlueString("insert target Chain size: ") << separatedChain.size() << std::endl;
	
	insertPendingChain(separatedChain, straggler); // straggler의 위치를 잘 설정해줘야 함.
	
	std::cout << Colors::BoldBlueString("inserted chain size: ") << separatedChain.size() << std::endl;
	
	// arranged chain의 순서대로 main chain의 인덱스를 변경해줘야 함.
	// index만 변경해주는 방법.
	// 이 방법은 최소 비교 알고리즘을 구현했다고는 할 수 없을 것 같다. 각 배열의 값을 비교하는 것을 n^2로 처리하는 게 말이 되나?
	mainChain = separatedChain;
	if (sequenceSize < mainChain.size())
	{
		std::cout << Colors::MagentaString("정렬을 모두 다 하고 return") << std::endl;
		if (straggler.content >= 0)
		{
			binarySearchDequeForOdd(mainChain, straggler);
		}
	}

}

void PmergeMe::sortMainChain(std::deque<Node>& mainChain, Node& straggler)
{
	sortingMainChainRecursively(mainChain, straggler);
	// if (straggler.content >= 0)
	// {
	// 	binarySearchDequeForOdd(mainChain, straggler);
	// }
	// 여기에는 mArgDeque에 넣어야 함.
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
	// std::sort(mainChain.begin(), mainChain.end());
	sortMainChain(mainChain, straggler);
	for (std::deque<Node>::iterator it = mainChain.begin(); it != mainChain.end(); it++)
	{
		mArgsDeque.push_back(it->content);
	}
	std::sort(test.begin(), test.end());
	std::cout << "[sorted]\n[deque] ";
	for (std::deque<int>::iterator it = test.begin(); it != test.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
}
