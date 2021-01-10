#include "../Lib/utils.h"

using namespace Ultra;

int main()
{
	printf("Open Test Explorer to run tests\n\n");
	printf("Two plus two is %d\n\n", utils::add(2, 2));

	uint32_t T = 11;
	std::vector<uint32_t> I { 1,2,3,4,5,6,7 };
	std::vector<uint32_t> M;
	uint32_t S;

	utils::find_largest_sum(T, I, M, S);

	printf("Given the integer %d and the following integer set:\n", T);
	for (auto &num : I)
	{
		printf("%d, ", num);
	}
	printf("\nA subset with the largest possible sum less than or equal to %d", T);
	printf(" has the sum %d and the following integer subset:\n", S);
	for (auto &num : M)
	{
		printf("%d, ", num);
	}
}