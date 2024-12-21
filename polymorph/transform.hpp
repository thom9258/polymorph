#pragma once

#include "detail.hpp"
#include "pipe.hpp"

namespace polymorph
{
	
template <typename F>
class transform_t : public traits::pipe_tag
{
	F f_;

public:
	explicit transform_t(F&& f) : f_(std::forward<F>(f)) {}

    template<typename V>
    constexpr auto process(const V& v) const noexcept
		-> std::vector<std::invoke_result_t<F, typename V::value_type>>
    {
		std::vector<std::invoke_result_t<F, typename V::value_type>> out{};
		out.reserve(v.size());
		for (size_t i = 0; i < v.size(); i++)
			out.push_back(std::invoke(f_, v[i]));

        return out;
    }
};
	
template <typename F>
[[nodiscard]] constexpr
transform_t<F> transform(F&& f) noexcept
{
	return transform_t<F>(f);
}


#if 0
template <typename F>
class apply_t : public traits::pipe_tag
{
	F f_;

public:
	explicit apply_t(F&& f) : f_(std::forward<F>(f)) {}

    template<typename V>
    constexpr auto process(const V& v) const noexcept
		-> decltype(auto)
		//-> std::vector<std::invoke_result_t<F, typename V::value_type::type>>
    {
		std::vector<std::invoke_result_t<F, std::tuple_element<std::index_sequence<std::tuple_size<V>>>::type...>> out{};
		out.reserve(v.size());
		for (size_t i = 0; i < v.size(); i++)
			out.push_back(std::apply(f_, v[i]));

        return out;
    }
};
	
template <typename F>
[[nodiscard]] constexpr
apply_t<F> apply(F&& f) noexcept
{
	return apply_t<F>(f);
}
#endif

}	
