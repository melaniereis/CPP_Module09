/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-31 13:17:13 by meferraz          #+#    #+#             */
/*   Updated: 2025-05-31 13:17:13 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

class BitCoinExchange
{
	public:
		BitCoinExchange(const std::string &filename);
		~BitCoinExchange();

	private:
		std::map<std::string, double> _exchangeRates;
		std::string _filename;
		bool _isValid;

		BitCoinExchange(const BitCoinExchange &other);
		BitCoinExchange &operator=(const BitCoinExchange &other);
		BitCoinExchange();
};
