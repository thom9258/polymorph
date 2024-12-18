#pragma once

#include "types.hpp"

namespace polymorph
{
	
template<concepts::Pipe Pipe, concepts::Collection Collection>
[[nodiscard]] constexpr
decltype(auto) operator>>=(Collection&& collection, Pipe&& pipe) noexcept
{
	return pipe.process(std::forward<Collection>(collection));
}
	
	
/**
 * Pipes are composed left-to-right, as can be seen in the construction of this class,
 * This can also be noted in the _compose_t::process() function.
*/
template <concepts::Pipe Lhs, concepts::Pipe2 Rhs>
class _compose_t : public traits::pipe_tag
{
	Lhs lhs_;
	Rhs rhs_;

public:
	explicit _compose_t(Lhs&& lhs, Rhs&& rhs) 
		: lhs_(std::forward<Lhs>(lhs))
		, rhs_(std::forward<Rhs>(rhs))
	{}

    template<typename V>
    constexpr decltype(auto) process(const V& v) const noexcept
    {
        return rhs_.process(lhs_.process(v));
    }
};

template <concepts::Pipe Lhs, concepts::Pipe2 Rhs>
[[nodiscard]] constexpr
decltype(auto) operator>>=(Lhs&& lhs, Rhs&& rhs) noexcept
{
	return _compose_t<Lhs, Rhs>(std::forward<Lhs>(lhs),
								std::forward<Rhs>(rhs));
}

}	
