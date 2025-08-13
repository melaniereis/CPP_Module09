/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:51:43 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/13 22:06:56 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"
#include "../inc/ansi.h"

/**
 * Default constructor
 *
 * Initializes an empty PmergeMe object.
 */
PmergeMe::PmergeMe() {}

/**
 * Copy constructor
 *
 * Creates a deep copy of the given PmergeMe object.
 *
 * @param other The object to copy from.
 */
PmergeMe::PmergeMe(const PmergeMe& other) {
	(void)other;
	// No members to copy in this case
}

/**
 * Destructor
 *
 * Cleans up the PmergeMe object.
 */
PmergeMe::~PmergeMe() {}

/**
 * Assignment operator
 *
 * Assigns the contents of another PmergeMe object to this one.
 *
 * @param other The object to assign from.
 * @return A reference to this object.
 */
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	// No members to copy in this case
	(void)other; // Avoid unused parameter warning
	return *this;
}

/**
 * Sorts the given vector using merge-insert sort and displays the result.
 *
 * @param vector The vector to sort.
 */
void PmergeMe::sortAndDisplay(const std::vector<int>& vector) {
	if (vector.empty()) {
		std::cout << BRED "❌ Error: The input vector is empty." RESET << std::endl;
		return;
	}
	std::cout << BBLU "📊 Before sorting the vector: " << RESET;
	for (size_t i = 0; i < vector.size(); ++i) {
		std::cout << vector[i] << (i < vector.size() - 1 ? ", " : "");
	}
	std::cout << std::endl;

	// Create a copy of the vector to sort
	std::vector<int> sortedVector = vector;
	clock_t start = clock();
	mergeInsertSort(sortedVector);
	clock_t end = clock();
	double vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	//Deque to display the sorted vector
	std::deque<int> deq(vector.begin(), vector.end());
	start = clock();
	mergeInsertSort(deq);
	end = clock();
	double deqTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::cout << BGRN "✅ After sorting the vector: " << RESET;
	for (size_t i = 0; i < sortedVector.size(); ++i) {
		std::cout << sortedVector[i] << (i < sortedVector.size() - 1 ? ", " : "");
	}
	std::cout << std::endl;
	 std::cout << BYEL "⏱️ Time to process a range of " << vector.size()
			<< " elements with std::vector: " << vecTime << " us" << RESET << std::endl;
	std::cout << BYEL "⏱️ Time to process a range of " << vector.size()
			<< " elements with std::deque: " << deqTime << " us" << RESET << std::endl;
}
