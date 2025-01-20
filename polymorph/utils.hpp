#pragma once

#include "detail.hpp"

namespace polymorph
{
namespace utils
{
	
template <concepts::Collection C>
constexpr size_t collection_length(C&& c)
{
	if constexpr (requires { c.size(); }) {
		return c.size();
	}

	return 0;
}
	
template <concepts::Collection C>
constexpr C& collection_reserve_additional(C&& c, size_t additional)
{
	if constexpr (requires { c.reserve(current_size(c) + additional); }) {
		c.reserve(collection_length(c) + additional);
	}
	return c;
}
	
template <concepts::Collection C, typename V>
constexpr C& collection_append(C&& c, V&& v)
{
	if constexpr (requires { c.push_back(std::forward<V>(v)); }) {
		c.push_back(std::forward<V>(v));
	}
	return c;
}

}
}
