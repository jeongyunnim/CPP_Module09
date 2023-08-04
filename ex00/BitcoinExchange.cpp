#include "BitcoinExchange.hpp"
// 2008/08/18일 이전 예외처리

std::map<std::string, double> BitcoinExchange::_exchangeRateData;

static int leapYearFeb(int year) {
	if (year % 4 == 0) {
		if (year % 100 != 0 || year % 400 == 0) {
			return (29);
		}
	}
	return (28);
}

static bool isValidPairOfDate(int year, int month, int day)
{
	int maxDay;

	switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			maxDay = 31;
			break ;
		case 4: case 6: case 9: case 11:
			maxDay = 30;
			break ;
		default:
			maxDay = leapYearFeb(year);
	}
	if (day > maxDay)
		return (false);
	return (true);
}

static bool	isValidDate(const std::string& date)
{
	std::stringstream dateStream(date);
	int	year;
	int	month;
	int	day;
	char dashFlag1;
	char dashFlag2;
	
	dateStream >> year >> dashFlag1 >> month >> dashFlag2 >> day;
	if (dashFlag1 != '-' || dashFlag2 != '-')
		return (false);
	if (dateStream.eof() == false || dateStream.fail() || year < 2008 || (month < 1 || 12 < month) || (day < 1 || day > 31) || \
		(year == 2008 && month < 8) || (year == 2008 && month < 8 && day < 18))
		return (false);
	if (isValidPairOfDate(year, month, day) == false)
		return (false);
	return (true);
}

static bool duplicateCheck(const std::string& date, const std::map<std::string, double>& map)
{
	std::map<std::string, double>::const_iterator it = map.find(date);
	
	if (it == map.end())
		return (true);
	return (false);
}

static bool isValidValueString(std::string& valueString, double& dValue)
{
	std::stringstream valueStream(valueString);
	valueStream >> dValue;
	if (valueStream.eof() == false || valueStream.fail() || dValue < 0 || dValue == std::numeric_limits<double>::infinity())
		return (false);
	return (true);
}

bool BitcoinExchange::databaseToMap(std::ifstream& database)
{
	std::string dateString;
	std::string valueString;
	double		dValue;

	std::getline(database, dateString, '\n');
	if (dateString != "date,exchange_rate")
	{
		std::cout << dateString << ": ";
		return (false);
	}
	while (database.eof() == false || database.fail() == false)
	{
		std::getline(database, dateString, ',');
		if (isValidDate(dateString) == false)
		{
			if (dateString.empty() == true)
				return (true);
			std::cout << dateString << ": ";
			return (false);
		}
		std::getline(database, valueString, '\n');
		if (isValidValueString(valueString, dValue) == false)
		{
			std::cout << valueString << ": ";
			return (false);
		}
		if (duplicateCheck(dateString, _exchangeRateData) == false)
		{
			std::cout << dateString << ": ";
			return (false);
		}
		_exchangeRateData.insert(std::pair<std::string, double>(dateString, dValue));
	}
	if (database.fail() == 1)
		return (false);
	return (true);
}

void printDatabaseMap(std::map<std::string, double> map)
{
	std::map<std::string, double>::iterator it = map.begin();
	std::map<std::string, double>::iterator ite = map.end();

	std::cout << "MAP" << std::endl;
	while (it != ite)
	{
		std::cout << Colors::BoldBlue << "KEY: [" << it->first << "]" << Colors::Reset << ": " << it->second << std::endl;
		it++;
	}
}

bool BitcoinExchange::parsingDataFile(const std::string& fileName)
{
	std::ifstream database(fileName);

	if (database.is_open() == false)
	{
		std::cout << Colors::Red << "Error: database file open error." << Colors::Reset << std::endl;
		return (false);
	}
	if (databaseToMap(database) == false)
	{
		std::cout << Colors::Red << "Error: database file is corrupted." << Colors::Reset << std::endl;
		return (false);
	}
	database.close();
	printDatabaseMap(_exchangeRateData);
	return (true);
}

// bool BitcoinExchange::parsingInputFile(const std::string& fileName)
// {

// }

// void BitcoinExchange::printExchangeRate(const std::string& date, const std::string& value)
// {

// }
