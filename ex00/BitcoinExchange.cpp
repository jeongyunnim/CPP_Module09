#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void) {}
BitcoinExchange::~BitcoinExchange(void) {}

BitcoinExchange* BitcoinExchange::_exchanger = NULL;

BitcoinExchange* BitcoinExchange::getInstance(void)
{
	if (_exchanger == NULL)
		_exchanger = new BitcoinExchange();
	return (_exchanger);
}

void BitcoinExchange::cleanUp(void)
{
	if (_exchanger != NULL)
		delete _exchanger;
}

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

static void	trimWhiteSpace(std::string& target)
{
	size_t	start = 0;

	while (start < target.size() && isspace(target[start]) == true)
	{
		start += 1;
	}
	target.erase(0, start);

	size_t	end = target.size() - 1;
	while (end > 0 && isspace(target[end]) == true)
	{
		end -= 1;
	}
	target.erase(end + 1);
}

static int	stringToInt(std::string& target)
{
	for (std::string::iterator it = target.begin(); it != target.end(); it++)
	{
		if (std::isdigit(*it) == false)
			return (-1) ;
	}
	return (std::atoi(target.c_str()));
}

static bool	isValidDate(const std::string& date)
{
	std::stringstream	dateStream(date);
	std::string			numString;
	int					year;
	int					month;
	int					day;

	std::getline(dateStream, numString, '-');
	year = stringToInt(numString);
	numString.clear();
	std::getline(dateStream, numString, '-');
	month = stringToInt(numString);
	numString.clear();
	std::getline(dateStream, numString, static_cast<char>(EOF));
	day = stringToInt(numString);
	numString.clear();
	if (year < 2008 || (month < 1 || 12 < month) || (day < 1 || day > 31) || \
		(year == 2008 && month < 8) || (year == 2008 && month < 8 && day < 18))
		return (false);
	if (isValidMonthOfDate(year, month, day) == false)
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
	trimWhiteSpace(dateString);
	if (isValidDate(dateString) == false)
		return (false);
	std::getline(oneLineStream, valueString, '\n');
	trimWhiteSpace(valueString);
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

	std::getline(database, oneLineString, ',');
	trimWhiteSpace(oneLineString);
	if (oneLineString != "date")
		return (false);
	std::getline(database, oneLineString);
	trimWhiteSpace(oneLineString);
	if (oneLineString != "exchange_rate")
		return (false);
	oneLineString.clear();
	std::getline(database, oneLineString);
	while (database.eof() == false || database.fail() == false)
	{
		trimWhiteSpace(oneLineString);
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
		std::cout << Colors::RedString("Error: database file open error.") << std::endl;
		return (false);
	}
	if (databaseToMap(database) == false)
	{
		std::cout << Colors::RedString("Error: database file is corrupted.") << std::endl;
		return (false);
	}
	database.close();
	return (true);
}

static bool isValidIntValueString(std::string valueString, double& dValue)
{
	std::stringstream valueStream(valueString);
	int dotFlag = 0;

	for (std::string::iterator it = valueString.begin(); it != valueString.end(); it++)
	{
		if (std::isdigit(*it) == true)
			continue ;
		else if (dotFlag == 0 && *it == '.')
			continue ;
		else
		{
			std::cout << Colors::RedString("Error: invalid input => ") << valueString << std::endl;
			return (false);
		}
	}
	valueStream >> dValue;
	if (valueStream.eof() == false)
	{
		std::cout << Colors::RedString("Error: invalid input => ") << valueString << std::endl;
		return (false);
	}
	else if (valueStream.fail() == true)
	{
		std::cout << Colors::RedString("Error: file stream error") << std::endl;
		return (false);
	}
	else if (dValue < 0)
	{
		std::cout << Colors::RedString("Error: not a positive input number => ") << valueString << std::endl;
		return (false);
	}
	else if (1000 < dValue)
	{
		std::cout << Colors::RedString("Error: too large a number => ") << valueString << std::endl;
		return (false);
	}
	return (true);
}

static double searchTargetValue(std::map<std::string, double>& _exchangeRateData, std::string date)
{
	std::map<std::string, double>::iterator it = _exchangeRateData.lower_bound(date);
	
	if (it->first == date || it == _exchangeRateData.begin()) ;
	else
		it--;
	return (it->second);
}

static void convertExchanges(std::string& oneLine, std::map<std::string, double>& _exchangeRateData)
{
	std::stringstream	oneLineStream(oneLine);
	std::string 		dateString;
	std::string 		delimeterString;
	std::string 		valueString;
	double				dValue;
	double				result;

	std::getline(oneLineStream, dateString, '|');
	trimWhiteSpace(dateString);
	if (oneLineStream.eof() || oneLineStream.fail() || isValidDate(dateString) == false)
	{
		std::cout << Colors::RedString("Error: bad input => ") << oneLine << std::endl;
		return ;
	}
	std::getline(oneLineStream, valueString, '\n');
	trimWhiteSpace(valueString);
	if ((oneLineStream.eof() == false || oneLineStream.fail() == true || valueString.empty() == true))
	{
		std::cout << Colors::RedString("Error: bad input => ") << oneLine << std::endl;
		return ;
	}
	if (isValidIntValueString(valueString, dValue) == false)
		return ;
	result = searchTargetValue(_exchangeRateData, dateString) * dValue;
	std::cout << Colors::Cyan << "Date[" << dateString << "]: " << Colors::Reset << result << std::endl;
	if (oneLineStream.eof() == false || oneLineStream.fail())
		std::cout << Colors::RedString("Error: file stream error") << std::endl;
}

void	BitcoinExchange::printExchangeRates(std::ifstream& input)
{
	std::string oneLineString;

	std::getline(input, oneLineString, '|');
	trimWhiteSpace(oneLineString);
	if (oneLineString != "date")
	{
		std::cout << Colors::RedString("Error: bad input => ") << oneLineString << std::endl;
		return ;
	}
	std::getline(input, oneLineString);
	trimWhiteSpace(oneLineString);
	if (oneLineString != "value")
	{
		std::cout << Colors::RedString("Error: bad input => ") << oneLineString << std::endl;
		return ;
	}
	std::getline(input, oneLineString);
	while (input.eof() == false || input.fail() == false)
	{
		if (_exchangeRateData.size() == 0)
			std::cout << Colors::RedString("Error: database is empty => ") << oneLineString << std::endl;
		convertExchanges(oneLineString, _exchangeRateData);
		oneLineString.clear();
		std::getline(input, oneLineString);
	}
	if (input.eof() == false && input.fail() == true)
	{
		std::cout << Colors::RedString("Error: file read error") << std::endl;
		return ;
	}
}

bool BitcoinExchange::parsingInputFile(const std::string& fileName)
{
	std::ifstream input(fileName);

	if (input.is_open() == false)
	{
		std::cout << Colors::RedString("Error: input file open error.") << std::endl;
		return (false);
	}
	printExchangeRates(input);
	input.close();
	return (true);
}
