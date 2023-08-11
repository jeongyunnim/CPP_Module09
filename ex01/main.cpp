#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << Colors::RedString("Error: argument count error") << std::endl;
		return (1);
	}
	RPN *calculator = RPN::getInstance();

	if (calculator->pushArguments(argv) == false)
		return (1);
	if (calculator->printResult() == false)
		return (1);

	RPN::cleanUp();
	return (0);
}