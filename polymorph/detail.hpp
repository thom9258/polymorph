#pragma once

#include <type_traits>
#include <concepts>
#include <vector>
#include <type_traits>
#include <functional>
#include <ostream>

namespace polymorph
{
	
namespace traits {

struct pipe_tag {};

};

namespace concepts {

// TODO [feature]: add more specifies for the pipe concept 
template<typename T>
concept Pipe = std::derived_from<std::remove_cvref_t<T>, traits::pipe_tag>;

// TODO: figure out if it is nessecary to specify an identical pipe concept for composing
template<typename T>
concept Pipe2 = std::derived_from<std::remove_cvref_t<T>, traits::pipe_tag>;

template<class C>
concept Collection = requires(C c, size_t i) {
	c.size();
	c[i];
};
	
// TODO [feature]: add more specifies for the collection concept 
#if 0
template<class C, class V>
concept Collection = requires(C c, V v, size_t i) {
	c.size();
	c[i];
	c<V>.push_back(v);
};
#endif
	
}
}
