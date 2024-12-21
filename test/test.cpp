#include <libtester/libtester.h>
#include <polymorph/polymorph.hpp>

#include <sstream>
#include <iostream>
#include <vector>
#include <string>


const std::vector<int> numbers = {1,2,3,4,5,6};

const auto multiply2 = [] (const int i) { return i*2; };
const auto add5 = [] (const int i) { return i+5; };
const auto is_even = [] (const int i) { return i % 2 == 0; };
const auto is_odd = [] (const int i) { return i % 2 == 1; };
const auto bool_to_str = [] (const bool b) -> std::string { return (b) ? "yes" : "no"; };
const auto greater_than_3 = [] (const int i) { return i > 3; };

void test_stream_correctly_omits_trailing_seperator_compared_to_simple_for_print()
{
	std::stringstream forprint{};
	for (const auto number: numbers)
		forprint << number << "-";;
	std::cout << "for-loop print: [" << forprint.str() << "]" << std::endl;
    TEST(forprint.str() == "1-2-3-4-5-6-");

	std::stringstream streamprint{};
	numbers >>= polymorph::stream(streamprint, "-");
	std::cout << "stream print:   [" << streamprint.str() << "]" << std::endl;
    TEST(streamprint.str() == "1-2-3-4-5-6");
	
    TEST(forprint.str() == streamprint.str() + "-");
	
	numbers >>= polymorph::stream(std::cout, "-", "\n");
	std::cout << "This should be a seperate line, stream supplied a endline ^" 
			  << std::endl;
}


template<typename A, typename B>
bool compare_vectors(A&& a, B&& b)
{
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

void test_transform()
{
	numbers >>= polymorph::stream(std::cout, " ", "\n");

	const auto doubles = polymorph::transform(multiply2).process(numbers);
	doubles >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(doubles, std::vector<int>{2,4,6,8,10,12}));

	const auto squareds = numbers >>= polymorph::transform(multiply2)
		                          >>= polymorph::transform(multiply2);

	squareds >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(squareds, std::vector<int>{4,8,12,16,20,24}));
}

void test_transform_between_types()
{
	numbers >>= polymorph::stream(std::cout, " ", "\n");

	const auto is_even_strings = numbers >>= polymorph::transform(is_even)
		                                 >>= polymorph::transform(bool_to_str);

	is_even_strings >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(is_even_strings,
						 std::vector<std::string>{"no", "yes","no","yes","no","yes"}));
}

void test_filter()
{
	numbers >>= polymorph::stream(std::cout, " ", "\n");
	const auto evens = numbers >>= polymorph::filter(is_even);
	evens >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(evens, std::vector<int>{2,4,6}));
	
	const auto odds = numbers >>= polymorph::filter(is_odd);
	odds >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(odds, std::vector<int>{1,3,5}));
	
	const auto over_3 = numbers >>= polymorph::filter(greater_than_3);
	over_3 >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(over_3, std::vector<int>{4,5,6}));
	
	const auto evens_over_3 = numbers >>= polymorph::filter(is_even)
		                              >>= polymorph::filter(greater_than_3);

	evens_over_3 >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(evens_over_3, std::vector<int>{4,6}));
}

void test_composing_transform_and_filter()
{
	numbers >>= polymorph::stream(std::cout, " ", "\n");
	const auto plus5_evens = numbers >>= polymorph::transform(add5)
	                                 >>= polymorph::filter(is_even);

	plus5_evens >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(plus5_evens, std::vector<int>{6,8,10}));
}

void test_simple_enumerate_printing()
{
	const std::vector<std::string> words{
		"Hello", " ", "everybody!", "\n", "I", " ", "am", "\t", "a", "string..",
	};
	words >>= polymorph::stream(std::cout, "", "\n");

	const auto is_space = [] (const std::string& s) {
		if (s == " " || s == "\f" || s == "\n" || s == "\r" || s == "\t" || s == "\v")
			return true;
		return false;
	};
	const auto is_not_space = [is_space] (const std::string& s) { return !is_space(s); };
	
	const auto nospace_words = words >>= polymorph::filter(is_not_space);
	nospace_words >>= polymorph::stream(std::cout, "", "\n");
	
	const auto print_enumerated = [] (const size_t i, const std::string& s) {
		std::cout << i << ") " << s << std::endl;
		return i;
	};
	
	const auto indices = nospace_words >>= polymorph::enumerate_transform(print_enumerated);
	indices >>= polymorph::stream(std::cout, " ", "\n");
}

using Person = std::tuple<std::string, size_t, bool>;
const std::vector<Person> people {
	Person{"Bob", 67, true},
	Person{"Alice", 37, false},
	Person{"Ash", 54, true},
	Person{"Nadia", 52, false},
	Person{"Po", 24, true},
};

const auto stringify_person = [] (const std::string& name,
								  const size_t age,
								  const bool gender) 
	-> std::string
{
	std::stringstream ss;
	ss << "Person: " << name 
	   << " age: " << age 
	   << " gender: " << std::string((gender) ? "male" : "female");
	return ss.str();
};

void test_enumerate()
{
	const auto is_male = [] (const polymorph::enumerated<Person>& person)
		-> bool 
	{
		return std::get<2>(person.value) == true; 
	};
	const auto is_over_30 = [] (const polymorph::enumerated<Person>& person)
		-> bool 
	{
		return std::get<1>(person.value) > 30; 
	};

	using indexed_name = std::tuple<size_t, std::string>;
	const auto take_indexed_name = [] (const polymorph::enumerated<Person>& person) 
		-> indexed_name
	{
		return {person.index, std::get<0>(person.value)};
	};
	const auto stringify_indexed_name = [] (const indexed_name& indexed_name) 
		-> std::string
	{
		std::stringstream ss;
		ss << std::get<0>(indexed_name) << ") " << std::get<1>(indexed_name);
		return ss.str();
	};

	const auto indexed_males_over_30 = people >>= polymorph::enumerate()
		                                      >>= polymorph::filter(is_male)
		                                      >>= polymorph::filter(is_over_30)
		                                      >>= polymorph::transform(take_indexed_name)
		                                      >>= polymorph::transform(stringify_indexed_name);

	indexed_males_over_30 >>= polymorph::stream(std::cout, "\n", "\n");

	TEST(compare_vectors(indexed_males_over_30, 
						 std::vector<std::string>{
							 "0) Bob",
							 "2) Ash"}));
}


#if 0

const auto stringify_person_tup = [&stringify_person] (const Person& person) 
	-> std::string
{
	const auto& [name, age, gender] = person;
	return stringify_person(name, age, gender);
};

void test_apply()
{
	const auto stringified_people_tup = people >>= polymorph::transform(stringify_person_tup);
	stringified_people_tup >>= polymorph::stream(std::cout, "\n", "\n");
	
	const auto stringified_people = people >>= polymorph::apply(stringify_person);
	stringified_people >>= polymorph::stream(std::cout, "\n", "\n");
}
#endif


void test_tee()
{
	numbers >>= polymorph::stream(std::cout, " ", "\n");
	std::stringstream ss{};
	
	const auto mult2_and_print = polymorph::transform(multiply2)
		                     >>= polymorph::stream(ss, " ", "");

	const auto plus5s = numbers >>= polymorph::tee(mult2_and_print)
		                        >>= polymorph::transform(add5);
	
	TEST(ss.str() == "2 4 6 8 10 12");
	std::cout << ss.str() << std::endl;
}

void test_partition()
{
	numbers >>= polymorph::stream(std::cout, " ", "\n");
	
	std::stringstream evens{};
	std::stringstream odds{};
	const auto same_numbers = numbers
		>>= polymorph::partition(is_even,
								 polymorph::stream(evens, " ", ""),
								 polymorph::stream(odds, " ", ""));
	
	TEST(evens.str() == "2 4 6");
	TEST(odds.str() == "1 3 5");
	TEST(compare_vectors(numbers, same_numbers));
}

void test_assign()
{
	numbers >>= polymorph::stream(std::cout, " ", "\n");
	
	std::vector<int> even{};
	std::vector<int> odd{};
	
	const auto all = numbers 
		>>= polymorph::transform(add5)
		>>= polymorph::partition(is_even,
								polymorph::assign(even)
								 >>= polymorph::stream(std::cout, " ", "\n"),
								polymorph::assign(odd)
								 >>= polymorph::stream(std::cout, " ", "\n"));

	TEST(compare_vectors(even, std::vector<int>{6, 8, 10}));
	TEST(compare_vectors(odd, std::vector<int>{7, 9, 11}));
}

void test_take()
{
	numbers >>= polymorph::stream(std::cout, " ", "\n");
	
	const auto half = numbers >>= polymorph::take(3);
	half >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(half, std::vector<int>{1, 2, 3}));
	
	const auto halfmult2 = numbers >>= polymorph::take(3)
		                           >>= polymorph::transform(multiply2);
	halfmult2 >>= polymorph::stream(std::cout, " ", "\n");
	TEST(compare_vectors(halfmult2, std::vector<int>{2, 4, 6}));
	
	const auto more = numbers >>= polymorph::take(numbers.size()*2)
		                      >>= polymorph::tee(polymorph::stream(std::cout, " ", "\n"));
	TEST(compare_vectors(more, std::vector<int>{1, 2, 3, 4, 5, 6}));
}


int main(int argc, char** argv)
{
    ltcontext_begin(argc, argv);

    TEST_UNIT(test_stream_correctly_omits_trailing_seperator_compared_to_simple_for_print());
    TEST_UNIT(test_transform());
    TEST_UNIT(test_transform_between_types());
    TEST_UNIT(test_filter());
    TEST_UNIT(test_composing_transform_and_filter());
    TEST_UNIT(test_simple_enumerate_printing());
    TEST_UNIT(test_enumerate());
    TEST_UNIT(test_tee());
    TEST_UNIT(test_partition());
    TEST_UNIT(test_assign());
    TEST_UNIT(test_take());

    ltcontext_end();
	return 0;
}
