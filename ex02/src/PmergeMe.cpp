/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:51:43 by meferraz          #+#    #+#             */
/*   Updated: 2025/07/22 15:42:07 by meferraz         ###   ########.fr       */
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

/**
 * Merges and sorts the given container using merge-insert sort.
 *
 * @tparam Container The type of the container (std::vector or std::deque).
 * @param container The container to sort.
 */
template <typename Container>
void PmergeMe::mergeInsertSort(Container& container) const
{
	if (container.size() <= 1) {
		return; // No need to sort if the container has 0 or 1 elements
	}

	// Group the elements into pairs and sort them
	typedef typename Container::iterator Iterator;
	typedef std::vector<std::pair<int, int> > PairVector;
	PairVector pairs;
	bool hasStraggler = (container.size() % 2 != 0);
	typename Container::value_type straggler;

	if (hasStraggler) {
		straggler = container.back();
		container.pop_back();
	}

	for (Iterator it = container.begin(); it != container.end(); it += 2) {
		Iterator next = it + 1;
	if (*it < *next) {
			pairs.push_back(std::make_pair(*next, *it));
		} else {
			pairs.push_back(std::make_pair(*it, *next));
		}
	}

	// Sort pairs based on larger element
	for (size_t i = 0; i < pairs.size(); ++i) {
		for (size_t j = i; j > 0 && pairs[j].first < pairs[j - 1].first; --j) {
			std::swap(pairs[j], pairs[j - 1]);
		}
	}

	//Recursively sort larger elements
	Container larger;
	for (size_t i = 0; i < pairs.size(); ++i) {
		larger.push_back(pairs[i].first);
	}
	mergeInsertSort(larger);

	//Build the sorted sequence
	Container sorted;
	for (size_t i = 0; i < larger.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (larger[i] == pairs[j].first) {
				sorted.push_back(pairs[j].second);
				break;
			}
		}
		sorted.push_back(larger[i]);
	}

	// Add the straggler element if it exists
	if (hasStraggler) {
		typename Container::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), straggler);
		sorted.insert(pos, straggler);
	}

	// Copy the sorted sequence back to the original container
	container = sorted;
}
