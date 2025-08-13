/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:08:47 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/13 22:07:15 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <utility>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		~PmergeMe();
		PmergeMe& operator=(const PmergeMe& other);

		void sortAndDisplay(const std::vector<int>& vector);

	private:
		template <typename Container>
		void mergeInsertSort(Container& container) const;
};

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
