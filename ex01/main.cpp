#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << Colors::RedString("Error: argument count error") << std::endl;
		return (1);
	}
	if (RPN::pushArguments(argv) == false)
		return (1);
	if (RPN::printResult() == false)
		return (1);
	return (0);
}