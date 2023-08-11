#include <sys/time.h>
#include <iomanip>
#include "PmergeMe.hpp"

long	getTime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 10000000 + tv.tv_usec);
}

int main(int argc, char *argv[])
{
	long startD;	
	long endD;	

	long startL;	
	long endL;

	if (argc < 2)
	{
		std::cout << Colors::RedString("Error: argument count error") << std::endl;
		return (1);
	}
	if (PmergeMe::pushArguments(argv) == false)
		return (1);
	PmergeMe::printRawArguments();
	startD = getTime();
	PmergeMe::mergeInsertionSortingDeque();
	endD = getTime();
	startL = getTime();
	PmergeMe::mergeInsertionSortingList();
	endL = getTime();
	PmergeMe::printArrangedArguments();

	std::cout << Colors::Cyan << "Time to process a range of " << PmergeMe::getRange() << " elements using " << Colors::BoldCyan << "deque: "<< Colors::Reset << std::fixed << std::setprecision(8) << static_cast<float>(endD - startD) / 1000 << " ms" << std::endl;
	std::cout << Colors::Cyan << "Time to process a range of " << PmergeMe::getRange() << " elements using " << Colors::BoldCyan << "list:  "<< Colors::Reset << std::fixed << std::setprecision(8) << static_cast<float>(endL - startL) / 1000 << " ms" << std::endl;
	return (0);
}