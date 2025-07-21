/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:37:45 by meferraz          #+#    #+#             */
/*   Updated: 2025/07/21 17:58:35 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>
#include <string>
#include <stdexcept>
#include <sstream>

class RPN
{
	public:
		RPN();
		RPN(const RPN &other);
		~RPN();
		RPN &operator=(const RPN &other);

		int evaluate(const std::string &expression);
	private:
		std::stack<int> _stack;

		void processToken(const std::string &token);
		bool isNumber(const std::string &token) const;
};
