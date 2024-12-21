#pragma once

#include "detail.hpp"
#include "pipe.hpp"

namespace polymorph
{
	
template <concepts::Pipe Pipe>
class tee_t : public traits::pipe_tag
{
	Pipe other_;

public:
	explicit tee_t(Pipe&& other) : other_(std::forward<Pipe>(other)) {}
	explicit tee_t(const Pipe& other) : other_(other) {}

    template<typename V>
    constexpr decltype(auto) process(const V& v) const noexcept
    {
		other_.process(v);
        return v;
    }
};
	
template <concepts::Pipe Pipe>
[[nodiscard]] constexpr
tee_t<Pipe> tee(Pipe&& other) noexcept
{
	return tee_t<Pipe>(std::forward<Pipe>(other));
}
	
template <concepts::Pipe Pipe>
[[nodiscard]] constexpr
tee_t<Pipe> tee(Pipe& other) noexcept
{
	return tee_t<Pipe>(other);
}
	
template <concepts::Pipe Pipe>
[[nodiscard]] constexpr
tee_t<Pipe> tee(const Pipe& other) noexcept
{
	return tee_t<Pipe>(other);
}

}	
