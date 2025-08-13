/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:29:50 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/13 21:53:38 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/BitCoinExchange.hpp"
#include "../inc/ansi.h"

/**
 * Default constructor
 *
 * Initializes an empty BitCoinExchange object.
 */
BitCoinExchange::BitCoinExchange() {}

/**
 * Copy constructor
 *
 * Creates a deep copy of the given BitCoinExchange object.
 *
 * @param other The object to copy from.
 */
BitCoinExchange::BitCoinExchange(const BitCoinExchange& other) {
	_database = other._database;
}

/**
 * Destructor
 *
 * Cleans up the BitCoinExchange object.
 */
BitCoinExchange::~BitCoinExchange() {}

/**
 * Assignment operator
 *
 * Assigns the contents of another BitCoinExchange object to this one.
 *
 * @param other The object to assign from.
 * @return A reference to this object.
 */
BitCoinExchange& BitCoinExchange::operator=(const BitCoinExchange& other) {
	if (this != &other)
	{
		_database = other._database;
	}
	return *this;
}

/**
 * Checks if the given year is a leap year.
 *
 * A leap year is a year that is exactly divisible by four, except for years
 * that are exactly divisible by 100, but these years are leap years if they
 * are exactly divisible by 400. For example, the years 1700, 1800, and 1900
 * are not leap years, but the years 1600 and 2000 are.
 *
 * @param year The year to check.
 * @return true if the year is a leap year, false otherwise.
 */
bool BitCoinExchange::isLeapYear(int year) const {
	if (year % 4 != 0) return false;
	if (year % 100 != 0) return true;
	return (year % 400 == 0);
}

/**
 * Checks if the given date string is in a valid format and represents a valid calendar date.
 *
 * The expected format is "YYYY-MM-DD", where:
 * - YYYY is a four-digit year.
 * - MM is a two-digit month (01 to 12).
 * - DD is a two-digit day.
 *
 * The function verifies:
 * - The format is correct with digits and hyphens at the appropriate positions.
 * - The month is between 1 and 12.
 * - The day is within valid range for the given month and year, accounting for leap years.
 *
 * @param date The date string to validate.
 * @return true if the date is valid, false otherwise.
 */

bool BitCoinExchange::isValidDate(const std::string& date) const {
	if (date.length() != 10) return false;
	for (int i = 0; i < 10; i++) {
		if (i == 4 || i == 7)
		{
			if (date[i] != '-') return false;
		} else if (!std::isdigit(date[i]))
		{
			return false;
		}
	}

	std::string yearStr = date.substr(0, 4);
	std::string monthStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);

	int year = std::atoi(yearStr.c_str());
	int month = std::atoi(monthStr.c_str());
	int day = std::atoi(dayStr.c_str());

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	if (month == 2)
	{
		if (isLeapYear(year))
		{
			if (day > 29) return false;
		} else
		{
			if (day > 28) return false;
		}
	} else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			return false;
	}
	return true;
}

/**
 * Checks if the given string is a valid positive float value within a reasonable range.
 *
 * The function verifies:
 * - The string can be converted to a float.
 * - The float value is positive.
 * - The float value is within a reasonable range (less than 1000).
 *
 * @param valueStr The string to validate.
 * @param value The validated float value.
 * @return true if the string is a valid positive float, false otherwise.
 */
bool BitCoinExchange::isValidValue(const std::string& valueStr, float& value) const {
	std::istringstream iss(valueStr);
	if (!(iss >> value))
	{
		std::cout << BRED "Error: bad input => " << valueStr << RESET << std::endl;
		return false;
	}

	char c;
	if (iss >> c)
	{
		std::cout << BRED "Error: bad input => " << valueStr << RESET << std::endl;
		return false;
	}

	if (value < 0)
	{
		std::cout << BRED "Error: not a positive number." RESET << std::endl;
		return false;
	}

	if (value > 1000)
	{
		std::cout << BRED "Error: too large a number." RESET << std::endl;
		return false;
	}
	return true;
}

/**
 * Finds the exchange rate for a given date.
 *
 * The function searches the database for an entry with a date equal to the given date.
 * If such an entry exists, the exchange rate associated with that entry is returned.
 *
 * If no entry with the given date exists, the function searches for the entry with the
 * closest date before the given date and returns the exchange rate associated with that entry.
 *
 * If no entry with a date before the given date exists, a std::runtime_error is thrown.
 *
 * @param date The date for which to find the exchange rate.
 * @return The exchange rate associated with the given date, or the closest date before that.
 * @throw std::runtime_error if no entry with a date before the given date exists.
 */
float BitCoinExchange::getExchangeRate(const std::string& date) const {
	std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
	if (it != _database.end() && it->first == date)
	{
		return it->second;
	}

	if (it == _database.begin())
	{
		throw std::runtime_error("no data available for this date or before.");
	}
	--it;
	return it->second;
}

/**
 * Loads the exchange rate database from a file.
 *
 * The file should contain a header line (which is skipped), followed by lines of the form:
 * date,rate
 * where date is a string in the format "YYYY-MM-DD" and rate is a float.
 *
 * The function reads the file line by line and stores each valid date and exchange rate in the
 * database.
 *
 * @param filename The name of the file to load the database from.
 * @throw std::runtime_error if the file cannot be opened.
 */
void BitCoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("could not open database file.");
	}

	std::string line;
	std::getline(file, line); // Skip header

	while (std::getline(file, line))
	{
		size_t pos = line.find(',');
		if (pos == std::string::npos) continue;

		std::string date = line.substr(0, pos);
		std::string rateStr = line.substr(pos + 1);

		std::istringstream iss(rateStr);
		float rate;
		iss >> rate;
		if (iss.fail()) continue;

		_database[date] = rate;
	}
}

/**
 * Processes a file containing lines of the form "date|value".
 *
 * The function reads the file line by line, and for each line, it extracts the date and value, and
 * prints to the console the date, value, and result of multiplying the value by the exchange rate
 * for that date. If the input line is invalid, an error message is printed instead.
 *
 * @param filename The name of the file to process.
 * @throw std::runtime_error if the file cannot be opened.
 */
void BitCoinExchange::processInputFile(const std::string& filename) const {
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("could not open file.");
	}

	std::string line;
	std::getline(file, line); // Skip header

	while (std::getline(file, line))
	{
		size_t pos;
		std::string date;
		std::string valueStr;
		float value;
		float rate;
		float result;

		pos = line.find('|');
		if (pos == std::string::npos)
		{
			std::cout << BRED "Error: bad input => " << line << RESET << std::endl;
			continue;
		}

		date = line.substr(0, pos);
		valueStr = line.substr(pos + 1);

		// Trim whitespace
		date.erase(date.find_last_not_of(" \t") + 1);
		date.erase(0, date.find_first_not_of(" \t"));
		valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
		valueStr.erase(0, valueStr.find_first_not_of(" \t"));

		if (!isValidDate(date))
		{
			std::cout << BRED "Error: bad input => " << date << RESET << std::endl;
			continue;
		}

		if (!isValidValue(valueStr, value))
		{
			continue;
		}

		try {
			rate = getExchangeRate(date);
			result = value * rate;
			std::cout << BGRN << date << " => " << valueStr << " = " << std::fixed << std::setprecision(2) << result << RESET << std::endl;
		} catch (const std::exception& e) {
			std::cout << BRED "Error: " << e.what() << RESET << std::endl;
		}
	}
}
