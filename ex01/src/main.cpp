/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:33:55 by meferraz          #+#    #+#             */
/*   Updated: 2025/07/21 17:57:15 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../inc/ansi.h"
#include "../inc/RPN.hpp"

#define SEPARATOR(txt) std::cout << "\n"                                              \
								<< BWHT "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"     \
								<< "📄 " << BBLU << txt << BWHT "\n"                 \
								<< "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n" \
								<< std::endl;

// ─────────────────────────────────────────────────────────────
// 📌 Function Declarations
// ─────────────────────────────────────────────────────────────


// ─────────────────────────────────────────────────────────────
// 🚀 main()
// ─────────────────────────────────────────────────────────────

int main(int argc, char **argv)
{
	std::cout << BGRN "\n\n📋===== RPN CALCULATOR SIMULATION =====📋\n\n" RESET;

	if (argc != 2)
	{
		std::cout << BRED "❌ Error: Invalid number of arguments." RESET
				  << " Usage: ./rpn \"<expression>\"" << std::endl;
		return 1;
	}

	try {
		RPN rpn;
		int result = rpn.evaluate(argv[1]);
		std::cout << BGRN "✅ Result: " BCYN << result << RESET << std::endl;
	} catch (const std::exception& e) {
		std::cerr << BRED "❌ Error: " << e.what() << RESET << std::endl;
		return 1;
	}

	return 0;
}

// ─────────────────────────────────────────────────────────────
// 🔧 Template function implementations
// ─────────────────────────────────────────────────────────────
