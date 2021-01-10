#pragma once

#include <vector>

namespace Ultra
{

	class utils
	{
	private:
		static void print_table(uint32_t T, const std::vector<uint32_t> &I, const std::vector<std::vector<bool>> &has_subset);

	public:
		static int add(int a, int b);
		static void find_largest_sum(uint32_t T, const std::vector<uint32_t> &I, std::vector<uint32_t>& M, uint32_t &S);
	};
}