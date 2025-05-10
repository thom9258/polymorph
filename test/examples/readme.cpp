#include <polymorph/polymorph.hpp>

void test_simple_example()
{
	const auto is_even = [] (const int i) { return i % 2 == 0; };
	const auto multiply_3 = [] (const int i) { return i*3; };
	const auto subtract_1 = [] (const int i) { return i-1; };

	const std::vector<int> numbers = {1,2,3,4,5,6};
	numbers 
		>>= polymorph::filter(is_even)
		>>= polymorph::transform(multiply_by_3)
		>>= polymorph::transform(subtract_1)
		>>= polymorph::to_stream(std::cout, " ", "\n");
}


int main(int argc, char** argv)
{
    test_simple_example();
	return 0;
}
