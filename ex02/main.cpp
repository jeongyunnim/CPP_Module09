#include "PmergeMe.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << Colors::RedString("Error: argument count error") << std::endl;
		return (1);
	}
	if (PmergeMe::pushArguments(argv) == false)
		return (1);
	PmergeMe::printArguments();
	PmergeMe::mergeInsertionSorting();
	/*

	1. 인자 파싱 OK
	2. 인자 출력
	3. 정렬된 수 출력
	4. 컨테이너1 정렬
	5. 컨테이너1 정렬 확인	<- 시간에 포함시키면 안되는데 
	6. 컨테이너1 정렬 시간 출력
	7. 컨테이너2 정렬
	8. 컨테이너2 정렬 확인
	9. 컨테이너2 정렬 시간 출력

	*/
	return (0);
}