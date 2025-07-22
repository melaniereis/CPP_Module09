/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:08:47 by meferraz          #+#    #+#             */
/*   Updated: 2025/07/22 15:38:48 by meferraz         ###   ########.fr       */
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
