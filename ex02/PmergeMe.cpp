#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {};
PmergeMe::~PmergeMe(void) {};

int	PmergeMe::findJacobsthalNum(int index)
{
	if (index == -1)
	{
		return (1);
	}
	return (mJacobsthalSequence[index]);
}

void PmergeMe::initJacobsthalSequence(void)
{
	bool	endFlag = false;
	int		jacobsthalIndex = 2;
	
	mJacobsthalSequence.push_back(1);
	mJacobsthalSequence.push_back(3);
	
	for (int jacobsthalNum = 0; endFlag == false; jacobsthalIndex++)
	{
		jacobsthalNum = mJacobsthalSequence[jacobsthalIndex - 1] + (2 * mJacobsthalSequence[jacobsthalIndex - 2]);
		mJacobsthalSequence.push_back(jacobsthalNum);
		if (jacobsthalNum > static_cast<int>(mArgsDeque.size()))
			endFlag = true;
	}

}
