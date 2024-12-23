#pragma once

#include "detail.hpp"

namespace polymorph
{
	

/**
 * Pipes are composed left-to-right, as can be seen in the construction of this class,
 * This can also be noted in the _compose_t::process() function.
*/
template <concepts::Pipe Lhs, concepts::Pipe Rhs>
class _compose_t : public traits::pipe_tag
{
	Lhs lhs_;
	Rhs rhs_;

public:
	explicit _compose_t(Lhs&& lhs, Rhs&& rhs) 
		: lhs_(std::forward<Lhs>(lhs))
		, rhs_(std::forward<Rhs>(rhs))
	{}
	
	explicit _compose_t(const Lhs& lhs, const Rhs& rhs) 
		: lhs_(lhs)
		, rhs_(rhs)
	{}

    template<typename V>
    constexpr decltype(auto) process(const V& v) const noexcept
    {
        return rhs_.process(lhs_.process(v));
    }
    template<typename V>
    constexpr decltype(auto) process(V&& v) const noexcept
    {
        return rhs_.process(lhs_.process(std::forward<V>(v)));
    }
};

template<concepts::Pipe Pipe, concepts::Collection Collection>
[[nodiscard]] constexpr
decltype(auto) operator>>=(Collection&& collection, Pipe&& pipe) noexcept
{
	return pipe.process(std::forward<Collection>(collection));
}
	
template<concepts::Pipe Pipe, concepts::Collection Collection>
[[nodiscard]] constexpr
decltype(auto) operator>>=(Collection&& collection, const Pipe& pipe) noexcept
{
	return pipe.process(std::forward<Collection>(collection));
}
	
template <concepts::Pipe Lhs, concepts::Pipe Rhs>
[[nodiscard]] constexpr
decltype(auto) operator>>=(Lhs&& lhs, Rhs&& rhs) noexcept
{
	return _compose_t<Lhs, Rhs>(std::forward<Lhs>(lhs),
								std::forward<Rhs>(rhs));
}
	
template <concepts::Pipe Lhs, concepts::Pipe Rhs>
[[nodiscard]] constexpr
decltype(auto) operator>>=(const Lhs& lhs, const Rhs& rhs) noexcept
{
	return _compose_t<Lhs, Rhs>(lhs, rhs);
}

}	
