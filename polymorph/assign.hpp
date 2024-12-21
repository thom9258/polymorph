#pragma once

#include "types.hpp"

namespace polymorph
{

template <concepts::Collection C>
class assign_t : public traits::pipe_tag
{
	C& c_;

public:
	explicit assign_t(C& c) : c_(c) {}

    template<typename V>
    constexpr decltype(auto) process(const V& v) const noexcept
    {
		if (!v.empty())
			c_ = v;
        return v;
    }
};
	
template <concepts::Collection C>
[[nodiscard]] constexpr
assign_t<C> assign(C& c) noexcept
{
	return assign_t<C>(c);
}

}
