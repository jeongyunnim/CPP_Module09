#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: argument count error" << std::endl;
		return (1);
	}

	BitcoinExchange *exchanger = BitcoinExchange::getInstance();
	if (exchanger->parsingDataFile("data.csv") == false)
	{
		BitcoinExchange::cleanUp();
		return (1);
	}
	if (exchanger->parsingInputFile(argv[1]) == false)
	{
		BitcoinExchange::cleanUp();
		return (1);
	}
		BitcoinExchange::cleanUp();

	return (0);
}