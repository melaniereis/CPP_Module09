/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:33:55 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/13 22:11:44 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <limits>
#include "../inc/ansi.h"
#include "../inc/PmergeMe.hpp"

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
	std::cout << BGRN "\n\n📋===== PMERGEME SIMULATION =====📋\n\n" RESET;

	if (argc < 2)
	{
		std::cout << BRED "❌ Error: Invalid number of arguments." RESET
				  << " Usage: ./pmergeMe <list of integers>" << std::endl;
		return 1;
	}

	std::vector<int> numbers;
	for (int i = 1; i < argc; ++i)
	{
		char *endptr;
		long num = std::strtol(argv[i], &endptr, 10);
		if (*endptr != '\0' || num < 0 || num > std::numeric_limits<int>::max())
		{
			std::cout << BRED "❌ Error: Invalid input '" << argv[i] << "'. Only positive integers are allowed." RESET << std::endl;
			return 1;
		}
		numbers.push_back(static_cast<int>(num));
	}

	try
	{
		PmergeMe sorter;
		sorter.sortAndDisplay(numbers);
	}
	catch (const std::exception& e)
	{
		std::cerr << BRED "❌ Error: " << e.what() << RESET << std::endl;
		return 1;
	}

	return 0;
}
