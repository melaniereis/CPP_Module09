/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 22:51:43 by meferraz          #+#    #+#             */
/*   Updated: 2025/08/16 09:30:39 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/PmergeMe.hpp"
#include "../inc/ansi.h"

/**
 * @brief Generates Jacobsthal indices for insertion order.
 *
 * This function generates Jacobsthal indices for insertion order. The Jacobsthal
 * indices are used in the algorithm of PmergeMe::insertPendingWithJacobsthal.
 * The function takes an integer n as input, which represents the number of elements
 * to be inserted. It returns a vector of size_t containing the Jacobsthal indices
 * up to n.
 *
 * @param n The number of elements to be inserted.
 *
 * @return A vector of size_t containing the Jacobsthal indices up to n.
 *
 * @throws None
 */
std::vector<size_t> PmergeMe::generateJacobsthalIndices(size_t n) const
{
	std::vector<size_t> indices;
	if (n == 0) return indices;
	indices.push_back(0);
	size_t k = 1;
	while (true)
	{
		size_t j = ((1 << (k + 1)) + ((k % 2 == 0) ? 1 : -1)) / 3;
		if (j - 1 >= n)
			break;
		indices.push_back(j - 1);
		++k;
	}
	return indices;
}

/**
 * @brief Splits a given container into two vectors of pairs where the first element of each pair
 * is larger than the second.
 *
 * This function takes a container of elements and splits it into two vectors - mainChain and
 * pending. The mainChain vector contains pairs of elements where the first element of the pair
 * is larger than the second. The pending vector contains pairs of elements where the first element
 * of the pair is smaller than the second. The input container must contain an even number of
 * elements.
 *
 * @tparam Container The type of the container to be split.
 * @param input The container to be split.
 * @param mainChain The vector where the pairs of elements where the first element of the pair is
 * larger than the second will be stored.
 * @param pending The vector where the pairs of elements where the first element of the pair is
 * smaller than the second will be stored.
 *
 * @throws None.
 */
template <typename Container>
void PmergeMe::splitIntoPairs(const Container& input,
	std::vector<typename Container::value_type>& mainChain,
	std::vector<typename Container::value_type>& pending) const
{
	typedef typename Container::const_iterator Iterator;
	Iterator it = input.begin();
	while (it != input.end())
	{
		typename Container::value_type first = *it;
		++it;
		if (it != input.end())
		{
			typename Container::value_type second = *it;
			if (first < second)
			{
				mainChain.push_back(second);
				pending.push_back(first);
			}
			else
			{
				mainChain.push_back(first);
				pending.push_back(second);
			}
			++it;
		}
		else
		{
			// Last odd element goes to mainChain
			mainChain.push_back(first);
		}
	}
}

/**
 * @brief Inserts the pending elements into the main chain using Jacobsthal order.
 *
 * This function takes a main chain and a vector of pending elements and inserts the
 * pending elements into the main chain using the Jacobsthal order. The main chain
 * is a container that supports random access iterator and has a value_type member.
 * The function does not modify the container size, but it does rearrange the
 * elements in the main chain.
 *
 * @tparam Container The type of the main chain container.
 * @param mainChain The main chain container.
 * @param pending The vector of pending elements to be inserted.
 */
template <typename Container>
void PmergeMe::insertPendingWithJacobsthal(Container& mainChain,
	const std::vector<typename Container::value_type>& pending) const
{
	if (pending.empty())
		return;

	std::vector<size_t> jacIndices = generateJacobsthalIndices(pending.size());
	std::vector<bool> inserted(pending.size(), false);

	// Insert pending elements in Jacobsthal order
	for (size_t idx = 0; idx < jacIndices.size(); ++idx) {
		size_t i = jacIndices[idx];
		if (i < pending.size() && !inserted[i]) {
			typename Container::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), pending[i]);
			mainChain.insert(pos, pending[i]);
			inserted[i] = true;
		}
	}
	// Insert remaining elements
	for (size_t i = 0; i < pending.size(); ++i) {
		if (!inserted[i]) {
			typename Container::iterator pos = std::upper_bound(mainChain.begin(), mainChain.end(), pending[i]);
			mainChain.insert(pos, pending[i]);
		}
	}
}

/**
 * @brief Sorts a given container using the mergeInsertSort algorithm.
 *
 * This function takes a container of elements and sorts it using the mergeInsertSort algorithm.
 * The container can be of any type that supports random access iterator and has a value_type member.
 * The function does not modify the container size, but it does rearrange the elements in ascending order.
 *
 * @tparam Container The type of the container to be sorted.
 * @param container The container to be sorted.
 *
 * @throws None.
 */
template <typename Container>
void PmergeMe::mergeInsertSort(Container& container) const
{
	if (container.size() <= 1)
		return;

	typedef typename Container::value_type ValueType;
	std::vector<ValueType> mainChain;
	std::vector<ValueType> pending;

	splitIntoPairs(container, mainChain, pending);

	Container sortedMainChain(mainChain.begin(), mainChain.end());
	mergeInsertSort(sortedMainChain);

	insertPendingWithJacobsthal(sortedMainChain, pending);

	container.assign(sortedMainChain.begin(), sortedMainChain.end());
}


/**
 * @brief Sorts the input vector using mergeInsertSort and prints the result along with the time taken.
 *        Also sorts the input vector using std::sort and checks if the results match.
 *
 * @param input The vector to be sorted.
 *
 * @throws None.
 */
void PmergeMe::sortAndDisplay(const std::vector<int>& input)
{
	if (input.empty())
	{
		std::cout << BRED "❌ Error: The input vector is empty." RESET << std::endl;
		return;
	}
	std::cout << BBLU "📊 Before sorting the vector: " << RESET;
	for (size_t i = 0; i < input.size(); ++i)
		std::cout << input[i] << (i < input.size() - 1 ? ", " : "");
	std::cout << std::endl;

	std::vector<int> sortedVector = input;
	clock_t start = clock();
	mergeInsertSort(sortedVector);
	clock_t end = clock();
	double vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::vector<int> stlSorted = input;
	std::sort(stlSorted.begin(), stlSorted.end());

	if (sortedVector != stlSorted)
	{
		std::cout << BRED "❌ Error: mergeInsertSort result does not match std::sort!" RESET << std::endl;
		std::cout << "Expected: ";
		for (size_t i = 0; i < stlSorted.size(); ++i)
			std::cout << stlSorted[i] << (i < stlSorted.size() - 1 ? ", " : "");
		std::cout << std::endl;
	}
	else
	{
		std::cout << BGRN "✅ mergeInsertSort result matches std::sort!" RESET << std::endl;
	}

	std::deque<int> deq(input.begin(), input.end());
	start = clock();
	mergeInsertSort(deq);
	end = clock();
	double deqTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

	std::cout << BGRN "✅ After sorting the vector: " << RESET;
	for (size_t i = 0; i < sortedVector.size(); ++i)
		std::cout << sortedVector[i] << (i < sortedVector.size() - 1 ? ", " : "");
	std::cout << std::endl;
	std::cout << BYEL "⏱️ Time to process a range of " << input.size()
			<< " elements with std::vector: " << vecTime << " us" << RESET << std::endl;
	std::cout << BYEL "⏱️ Time to process a range of " << input.size()
			<< " elements with std::deque: " << deqTime << " us" << RESET << std::endl;
}

/* ************************************************************************** */
/*                        *****CANONICAL FORM******                           */
/* ************************************************************************** */

/**
 * @brief Default constructor for PmergeMe.
 *
 * Initializes all member variables to their default values.
 */
PmergeMe::PmergeMe()
{}

/**
 * @brief Copy constructor for PmergeMe.
 *
 * This constructor creates a deep copy of the input PmergeMe object.
 *
 * @param other The PmergeMe object to be copied.
 */
PmergeMe::PmergeMe(const PmergeMe& other)
{
	(void)other;
}

/**
 * @brief Destructor for PmergeMe.
 *
 * This destructor is responsible for deallocating any dynamically allocated
 * memory.
 */
PmergeMe::~PmergeMe()
{}
/**
 * @brief Assignment operator for PmergeMe.
 *
 * This operator assigns the contents of another PmergeMe object to this one.
 *
 * @param other The PmergeMe object to be assigned.
 * @return A reference to this PmergeMe object.
 */
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void)other;
	return *this;
}
