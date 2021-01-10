#include "utils.h"
#include <iostream>
#include <algorithm>

namespace Ultra
{
	int utils::add(int a, int b) {
		// the sum is calculated using XOR
		int sum = a ^ b;
		// the carry is calculated using AND
		int carry = a & b;

		// When the carry = 0, the sum is complete
		while (carry)
		{
			// shift the carry one bit to the left
			int shifted_carry = carry << 1;
			// the new carry is
			carry = sum & shifted_carry;
			// apply the shifted carry into the sum
			sum ^= shifted_carry;
		}

		// get number of bits in int type
		const int int_bits = sizeof(int) * 8;
		// Get the sign bit of a, b and the final sum
		// Cast to unsigned int first, as shifting signed int does not shift sign bit
		const int a_sign = (unsigned int)a >> (int_bits - 1);
		const int b_sign = (unsigned int)b >> (int_bits - 1);
		const int sum_sign = (unsigned int)sum >> (int_bits - 1);

		// if the signs of a and b are the same, but the sign of the sum is different, this is an overflow
		if ((a_sign ^ b_sign ^ 1) & (a_sign ^ sum_sign))
		{
			throw std::overflow_error("arithmetic overflow");
		}

		return sum;
	}

	// prints the largest sum table
	// Will look legible for T<= 99 and integers in set I <= 9999
	// Note: to view full correct table, remove the loop break when finding the first max_sum
	void utils::print_table(uint32_t T, const std::vector<uint32_t> &I, const std::vector<std::vector<bool>> &has_subset)
	{
		for (uint32_t i = 0; i <= I.size(); i++)
		{
			if (i > 0)
			{
				printf("%4u  ", I[i - 1]);
			}
			else
			{
				printf("     ");
				for (uint32_t j = 0; j <= T; j++) {
					printf("%2u ", j);
				}
				printf("\n\n   0  ");
			}
			for (uint32_t j = 0; j <= T; j++) {
				char printed = 'F';
				if (has_subset[i][j])
				{
					printed = 'T';
				}
				printf("%c  ", printed);
			}
			printf("\n\n");
		}
	}

	void utils::find_largest_sum(uint32_t T, const std::vector<uint32_t> &I, std::vector<uint32_t>& M, uint32_t &S)
	{
		// get the set size
		const uint32_t n = I.size();
		// has_subset[i][j] is true if there exists
		// a subset of the set I up to the i-1th element
		// with a sum equal to j
		// The 2D vector dimensions are one larger than the set size by one larger than T,
		// to allow for storing of the base cases of 0 sum and empty set
		std::vector<std::vector<bool>> has_subset(n + 1, std::vector<bool>(T + 1));

		// For the base case of 0 sum, there exists an appropriate set for every i
		for (uint32_t i = 0; i <= n; i++)
			has_subset[i][0] = true;

		// For the base case of empty set and sum > 0, there does not exist an appropriate set for any j  
		for (uint32_t j = 1; j <= T; j++)
			has_subset[0][j] = false;

		bool sum_found = false;
		S = 0;
		uint32_t winning_subset = 0;
		// Fill in the has_subset table using dynamic programming tabulation method
		for (uint32_t i = 1; i <= n; i++) {
			for (uint32_t j = 1; j <= T; j++) {
				// If the value in the set with index i is greater than max sum
				// the set ending at index i is true only if
				// the set ending at index i-1 is true
				if (j < I[i - 1])
				{
					has_subset[i][j] = has_subset[i - 1][j];
				}
				// Otherwise, the set ending at index i is true both if
				// the set ending at index i-1 is true
				// OR the the set at index i-1 with sum j less than the value of the current element is true
				else
				{
					has_subset[i][j] = has_subset[i - 1][j] || has_subset[i - 1][j - I[i - 1]];
				}
				// If we have found a new max sum
				if (has_subset[i][j] && j > S)
				{
					// set the sum and store the subset index
					S = j;
					winning_subset = i;
					if (S == T)
					{
						// if the max sum has already been found, no need to keep looking for other subsets
						sum_found = true;
						break;
					}
				}
			}
			// break out of the outer loop as well
			if (sum_found)
			{
				break;
			}
		}

		// print table for debugging
		//print_table(T, I, has_subset);

		M = std::vector<uint32_t>{};

		uint32_t i = winning_subset;
		uint32_t j = S;

		// Unravel the table and find the integers which add up to the winning sum
		while (j > 0)
		{
			// if the previous index subset also has a winning subset, use that instead
			if (has_subset[i - 1][j])
			{
				i--;
			}
			else
			{
				// Otherwise, insert the current element
				M.insert(M.begin(), I[i - 1]);
				// Reduce j by the value of the inserted element
				j -= I[i - 1];
				// Decrement the subset index
				i--;
			}
		}
	}

}