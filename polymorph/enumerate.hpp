#pragma once

#include "detail.hpp"
#include "pipe.hpp"

namespace polymorph
{

template<typename V>
struct enumerated
{
	enumerated(size_t index, V value) : index(index), value(value) {}
	size_t index;
	V value;
};
	
class enumerate_t : public traits::pipe_tag
{
public:
	explicit enumerate_t() {}

    template<typename V>
    decltype(auto) process(const V& v) const noexcept
    {
		std::vector<enumerated<typename V::value_type>> out{};
		out.reserve(v.size());
		for (size_t i = 0; i < v.size(); i++)
			out.emplace_back(i, v[i]);

        return out;
    }
};
	
[[nodiscard]] 
enumerate_t enumerate() noexcept
{
	return enumerate_t();
}
	
template <typename F>
class enumerate_transform_t : public traits::pipe_tag
{
	F f_;

public:
	explicit enumerate_transform_t(F&& f) : f_(std::forward<F>(f)) {}

    template<typename V>
    constexpr auto process(const V& v) const noexcept
		-> std::vector<std::invoke_result_t<F, size_t, typename V::value_type>>
    {
		std::vector<std::invoke_result_t<F, size_t, typename V::value_type>> out{};
		out.reserve(v.size());
		for (size_t i = 0; i < v.size(); i++)
			out.push_back(std::invoke(f_, i, v[i]));

        return out;
    }
};
	
template <typename F>
[[nodiscard]] constexpr
enumerate_transform_t<F> enumerate_transform(F&& f) noexcept
{
	return enumerate_transform_t<F>(f);
}
	
}	
