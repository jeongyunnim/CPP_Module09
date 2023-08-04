#include "BitcoinExchange.hpp"

std::map<std::string, double> BitcoinExchange::_exchangeRateData;

static int leapYearFeb(int year) {
	if (year % 4 == 0) {
		if (year % 100 != 0 || year % 400 == 0) {
			return (29);
		}
	}
	return (28);
}

static bool isValidMonthOfDate(int year, int month, int day)
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
	{
		std::cout << dashFlag1 << dashFlag2 << std::endl;
		return (false);
	}
	if (dateStream.eof() == false || dateStream.fail() || year < 2008 || (month < 1 || 12 < month) || (day < 1 || day > 31) || \
		(year == 2008 && month < 8) || (year == 2008 && month < 8 && day < 18))
	{
		std::cout << dateStream.str() << std::endl;
		return (false);
	}
	if (isValidMonthOfDate(year, month, day) == false)
	{
		std::cout << dateStream.str() << std::endl;
		return (false);
	}
	return (true);
}

static bool duplicateCheck(const std::string& date, const std::map<std::string, double>& map)
{
	std::map<std::string, double>::const_iterator it = map.find(date);
	
	if (it == map.end())
		return (true);
	return (false);
}

static bool isValidDoubleValueString(std::string& valueString, double& dValue)
{
	std::stringstream valueStream(valueString);
	valueStream >> dValue;
	if (valueStream.eof() == false || valueStream.fail() || dValue < 0 || dValue == std::numeric_limits<double>::infinity())
		return (false);
	return (true);
}

static bool isValidOneLine(std::string& oneLine, std::map<std::string, double>& _exchangeRateData)
{
	std::stringstream	oneLineStream(oneLine);
	std::string 		dateString;
	std::string 		valueString;
	double				dValue;

	std::getline(oneLineStream, dateString, ',');
	if (isValidDate(dateString) == false)
		return (false);
	std::getline(oneLineStream, valueString, '\n');
	if (isValidDoubleValueString(valueString, dValue) == false)
		return (false);
	if (duplicateCheck(dateString, _exchangeRateData) == false)
		return (false);
	_exchangeRateData.insert(std::pair<std::string, double>(dateString, dValue));
	if (oneLineStream.eof() == false || oneLineStream.fail())
		return (false);
	return (true);
}

bool BitcoinExchange::databaseToMap(std::ifstream& database)
{
	std::string oneLineString;

	std::getline(database, oneLineString, '\n');
	if (oneLineString != "date,exchange_rate")
	{
		std::cout << oneLineString << ": ";
		return (false);
	}
	std::getline(database, oneLineString);
	while (database.eof() == false || database.fail() == false)
	{
		if (isValidOneLine(oneLineString, _exchangeRateData) == false)
			return (false);
		oneLineString.clear();
		std::getline(database, oneLineString);
	}
	if (database.eof() == false && database.fail() == true)
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
	// printDatabaseMap(_exchangeRateData);
	return (true);
}

static bool isValidIntValueString(std::string& valueString, double& dValue)
{
	std::stringstream valueStream(valueString);
	valueStream >> dValue;
	if (valueStream.eof() == false || valueStream.fail() || dValue < 0 || 1000 < dValue)
		return (false);
	return (true);
}

static double searchTargetValue(std::map<std::string, double>& _exchangeRateData, std::string date)
{
	std::map<std::string, double>::iterator it = _exchangeRateData.lower_bound(date);
	
	std::cout << "date: " << date << "[map] <" << it->first << "> -> " << it->second << std::endl;
	// if (it->first == date)
	// 	return (it->second);
	// else (it->first == date)
	return (it->second);
}

static bool convertExchanges(std::string& oneLine, std::map<std::string, double>& _exchangeRateData)
{
	std::stringstream	oneLineStream(oneLine);
	std::string 		dateString;
	std::string 		delimeterString;
	std::string 		valueString;
	double				dValue;
	double				result;

	std::getline(oneLineStream, dateString, ' ');
	if (oneLineStream.eof() || oneLineStream.fail() || isValidDate(dateString) == false)
		return (false);
	std::getline(oneLineStream, delimeterString, ' ');
	if (oneLineStream.eof() || oneLineStream.fail() || delimeterString != "|")
		return (false);
	std::getline(oneLineStream, valueString, '\n');
	if (oneLineStream.eof() == false || oneLineStream.fail() == true)
		return (false);
	if (isValidIntValueString(valueString, dValue) == false)
		return (false);
	result = searchTargetValue(_exchangeRateData, dateString) * dValue;
	//찾기 -> 밸류 값 곱해서 출력하기.
	if (oneLineStream.eof() == false || oneLineStream.fail())
		return (false);
	return (true);
}

void	BitcoinExchange::printExchangeRates(std::ifstream& input)
{
	std::string oneLineString;

	std::getline(input, oneLineString, '\n');
	if (oneLineString != "date | value")
	{
		std::cout << Colors::Red << "Error: bad input => " << oneLineString << Colors::Reset << std::endl;
		return ;
	}
	std::getline(input, oneLineString);
	while (input.eof() == false || input.fail() == false)
	{
		if (_exchangeRateData.size() == 0)
			std::cout << Colors::Red << "Error: database is empty => " << oneLineString << Colors::Reset << std::endl;
		else if (convertExchanges(oneLineString, _exchangeRateData) == false)
			std::cout << Colors::Red << "Error: bad input => " << oneLineString << Colors::Reset << std::endl;
		oneLineString.clear();
		std::getline(input, oneLineString);
	}
	if (input.eof() == false && input.fail() == true)
	{
		std::cout << Colors::Red << "Error: file read error" << Colors::Reset << std::endl;
		return ;
	}
}

bool BitcoinExchange::parsingInputFile(const std::string& fileName)
{
	std::ifstream input(fileName);

	if (input.is_open() == false)
	{
		std::cout << Colors::Red << "Error: input file open error." << Colors::Reset << std::endl;
		return (false);
	}
	// std::cout << "oh" << std::endl;
	printExchangeRates(input);
	input.close();
	return (true);
}
