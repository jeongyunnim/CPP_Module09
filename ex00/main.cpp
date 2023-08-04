#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: argument count error" << std::endl;
		return (1);
	}
	BitcoinExchange::parsingDataFile("data.csv");
	// BitcoinExchange::parsingInputFile(argv[1]);
	return (0);
}