/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:39:07 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/16 10:44:53 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/RPN.hpp"
#include "../inc/ansi.h"

/**
 * Default constructor
 *
 * Initializes an empty RPN object.
 */
RPN::RPN() {}

/**
 * Copy constructor
 *
 * Creates a deep copy of the given RPN object.
 *
 * @param other The object to copy from.
 */
RPN::RPN(const RPN &other)
{
	_stack = other._stack;
}

/**
 * Destructor
 *
 * Cleans up the RPN object.
 */
RPN::~RPN() {}

/**
 * Assignment operator
 *
 * Assigns the contents of another RPN object to this one.
 *
 * @param other The object to assign from.
 * @return A reference to this object.
 */
RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		_stack = other._stack;
	}
	return *this;
}

/**
 * Checks if a given token is a valid number.
 *
 * A valid number is a string that represents an integer, optionally starting
 * with a minus sign.
 *
 * @param token The token to check.
 * @return true if the token is a valid number, false otherwise.
 */
bool RPN::isNumber(const std::string &token) const
{
	for (size_t i = 0; i < token.length(); i++) {
		if (!std::isdigit(token[i]) && !(i == 0 && token[i] == '-')) {
			return false;
		}
	}
	return true;
}

/**
 * Evaluates a Reverse Polish Notation expression.
 *
 * The function processes each token in the expression, performing operations
 * based on the token type (number or operator). It uses a stack to manage
 * the operands and results.
 *
 * @param expression The RPN expression to evaluate.
 * @return The result of the evaluation.
 * @throw std::runtime_error if the expression is invalid.
 */
int RPN::evaluate(const std::string &expression)
{
	// Clear the stack before evaluation, not really necessary but good practice because in main function we instance RPN object only once
	while (!_stack.empty())
		_stack.pop();

	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		try
		{
			processToken(token);
		} catch (const std::runtime_error &e)
		{
			throw std::runtime_error(e.what());
		}
	}

	if (_stack.size() != 1)
	{
		throw std::runtime_error("Invalid RPN expression");
	}

	return _stack.top();
}

/**
 * Processes a single token in the RPN expression.
 *
 * If the token is a number, it is pushed onto the stack.
 * If the token is an operator, the top two elements are popped from the stack,
 * the operation is performed, and the result is pushed back onto the stack.
 *
 * @param token The token to process.
 * @throw std::runtime_error if an invalid token is encountered or if there are not enough operands.
 */
void RPN::processToken(const std::string &token)
{
	if (token == "+" || token == "-" || token == "*" || token == "/")
	{
		if (_stack.size() < 2)
		{
			throw std::runtime_error("Not enough operands");
		}

		int a = _stack.top();
		_stack.pop();
		int b = _stack.top();
		_stack.pop();

		if (token == "+")
		{
			_stack.push(b + a);
		}
		else if (token == "-")
		{
			_stack.push(b - a);
		}
		else if (token == "*")
		{
			_stack.push(b * a);
		}
		else if (token == "/")
		{
			if (a == 0)
			{
				throw std::runtime_error("Division by zero");
			}
			_stack.push(b / a);
		}
	}
	else if (isNumber(token))
	{
		std::istringstream iss(token);
		int num;
		iss >> num;
		_stack.push(num);
	}
	else
	{
		throw std::runtime_error("Invalid token: '" + token + "'");
	}
}
