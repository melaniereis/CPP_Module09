/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:17:13 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/13 21:49:43 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

class BitCoinExchange
{
	public:
		BitCoinExchange();
		BitCoinExchange(const BitCoinExchange& other);
		~BitCoinExchange();
		BitCoinExchange& operator=(const BitCoinExchange& other);

		void loadDatabase(const std::string& filename);
		void processInputFile(const std::string& filename) const;

	private:
		std::map<std::string, float> _database;

		bool isValidDate(const std::string& date) const;
		bool isLeapYear(int year) const;
		bool isValidValue(const std::string& valueStr, float& value) const;
		float getExchangeRate(const std::string& date) const;

};
