/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:33:55 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/13 21:55:23 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/ansi.h"
#include "../inc/BitCoinExchange.hpp"

#define SEPARATOR(txt) std::cout << "\n"                                              \
								<< BWHT "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"     \
								<< "📄 " << BBLU << txt << BWHT "\n"                 \
								<< "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n" \
								<< std::endl;

// ─────────────────────────────────────────────────────────────
// 🚀 main()
// ─────────────────────────────────────────────────────────────

int main(int argc, char **argv)
{
	std::cout << BGRN "\n\n📋===== BITCOIN EXCHANGE SIMULATION =====📋\n\n" RESET;

	if (argc != 2)
	{
		std::cout << BRED "❌ Error: Invalid number of arguments." RESET
				<< "Usage: ./btc <input_file>" << std::endl;
		return 1;
	}

	BitCoinExchange exchange;
	try {
		exchange.loadDatabase("data.csv");
		exchange.processInputFile(argv[1]);
	} catch (const std::exception& e) {
		std::cerr << BRED "❌ Error: " << e.what() << RESET << std::endl;
		return 1;
	}

	return 0;
}
