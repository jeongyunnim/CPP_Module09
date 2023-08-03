#include "BitcoinExchange.hpp"
// 2008/08/18일 이전 예외처리
/*
	1월(1월): 31일
	2월(2월): 28일(평년), 29일(윤년)
	3월(3월): 31일
	4월(4월): 30일
	5월(5월): 31일
	6월(6월): 30일
	7월(7월): 31일
	8월(8월): 31일
	9월(9월): 30일
	10월(10월): 31일
	11월(11월): 30일
	12월(12월): 31일
*/

bool isLeapYear(int year) {
	if (year % 4 == 0) {
		if (year % 100 != 0 || year % 400 == 0) {
			return true;
		}
	}
	return false;
}

static bool isValidPairOfDate(int year, int month, int day)
{
	switch (month)
	{
		case 1:
			if (day < 31)
			break ;
		
	}

}

static bool	isValidDate(const std::string& date)
{
	std::stringstream dateStream(date);
	int	year;
	int	month;
	int	day;
	char dotFlag;
	
	dateStream >> year;
	dotFlag = dateStream.get();
	if (dotFlag != '-')
		return (false);
	dateStream >> month;
	dotFlag = dateStream.get();
	if (dotFlag != '-')
		return (false);
	dateStream >> day;
	if (dateStream.eof() == false || year < 2008 || (month < 1 || 12 < month) || (day < 1 || day > 31) || \
		(year == 2008 && month < 8) || (year == 2008 && month < 8 && day < 18))
		return (false);
	if (isValidPairOfDate(year, month, day) == false)
		return (false);
	return (true);
}

static bool databaseFileValidCheck(std::ifstream& database)
{
	std::string dateString;
	std::string valueString;

	while (database.eof() == 1 || database.fail() == 1)
	{
		std::getline(database, dateString, ',');
		if (isValidDate(dateString) == false)
			return (false);
		std::getline(database, valueString, '\n');
		if (std::strtod(valueString.c_str(), NULL) < 0)
			return (false);
	}
	if (database.fail() == 1)
		return (false);
	return (true);
}


bool BitcoinExchange::parsingDataFile(const std::string& fileName)
{
	std::ifstream database;

	if (database.is_open() == 0)
	{
		std::cout << "Error: database file open error." << std::endl;
		return (false);
	}
	databaseFileValidCheck(database);
	database.close();
	return (true);
}

bool BitcoinExchange::parsingInputFile(const std::string& fileName)
{

}

void BitcoinExchange::printExchangeRate(const std::string& date, const std::string& value)
{

}
