#pragma once

#include "utils.hpp"
#include "pipe.hpp"

namespace polymorph
{

template<typename V>
class enumerated
{
public:
	explicit enumerated(const size_t index, V&& value) 
		: m_index(index), m_value(std::move(value)) 
	{
	}

	explicit enumerated(const size_t index, const V& value) 
		: m_index(index), m_value(value) 
	{
	}

	size_t index() const noexcept {return m_index; }
	decltype(auto) value() const noexcept {return m_value; }
	decltype(auto) value() noexcept {return m_value; }
	decltype(auto) operator*() const noexcept {return value(); }
	decltype(auto) operator*() noexcept {return value(); }
	
private:
	size_t m_index;
	V m_value;
};
	
class enumerate_t : public traits::pipe_tag
{
public:
	explicit enumerate_t() {}

    template<typename V>
    decltype(auto) process(const V& v) const noexcept
    {
		std::vector<enumerated<typename V::value_type>> out{};
		utils::collection_reserve_additional(out, utils::collection_length(v));
		for (size_t i = 0; i < utils::collection_length(v); i++)
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
		utils::collection_reserve_additional(out, utils::collection_length(v));
		for (size_t i = 0; i < utils::collection_length(v); i++)
			utils::collection_append(out, std::invoke(f_, i, v[i]));

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
