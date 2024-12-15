#pragma once

#include "types.hpp"

namespace polymorph
{

template <typename P>
class filter_t : public traits::pipe_tag
{
	P p_;

public:
	explicit filter_t(P&& p) : p_(std::forward<P>(p)) {}

    template<typename V>
    constexpr auto process(const V& v) const noexcept
		-> std::remove_cvref_t<V>
    {
		std::remove_cvref_t<V> out{};
		for (size_t i = 0; i < v.size(); i++)
			if (std::invoke(p_, v[i]) == true)
				out.push_back(v[i]);
        return out;
    }
};
	
template <typename P>
[[nodiscard]] constexpr
filter_t<P> filter(P&& p) noexcept
{
	return filter_t<P>(p);
}
	
}
