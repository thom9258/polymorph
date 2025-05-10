
#include <polymorph/polymorph.hpp>

#include <vector>
#include <iostream>

bool is_even(int v) { return v % 2 == 0; }

int main() {
    std::vector<int> numbers {1, 2, 3, 4};
	numbers 
		>>= polymorph::filter(is_even)
		>>= polymorph::transform([] (int v) {return std::to_string(v); })
		>>= polymorph::stream(std::cout, " ", "\n");
}
