/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:08:47 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/16 08:55:19 by meferraz         ###   ########.fr       */
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
#include <cstddef>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		~PmergeMe();
		PmergeMe& operator=(const PmergeMe& other);

		void sortAndDisplay(const std::vector<int>& vector);

	private:
		// Ford-Johnson main sort
		template <typename Container>
		void mergeInsertSort(Container& container) const;

		// Split input into pairs (larger to mainChain, smaller to pending)
		template <typename Container>
		void splitIntoPairs(const Container& input,
			std::vector<typename Container::value_type>& mainChain,
			std::vector<typename Container::value_type>& pending) const;

		// Insert pending elements using Jacobsthal order
		template <typename Container>
		void insertPendingWithJacobsthal(Container& mainChain,
			const std::vector<typename Container::value_type>& pending) const;

		// Generate Jacobsthal indices for insertion order
		std::vector<size_t> generateJacobsthalIndices(size_t n) const;
};
