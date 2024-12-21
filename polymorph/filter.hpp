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
	

template <typename P, concepts::Pipe OkPipe, concepts::Pipe2 NokPipe>
class partition_t : public traits::pipe_tag
{
	P p_;
	OkPipe ok_pipe_;
	NokPipe nok_pipe_;

public:
	explicit partition_t(P&& p, OkPipe&& ok_pipe, NokPipe&& nok_pipe)
		: p_(std::forward<P>(p)) 
		, ok_pipe_(std::forward<OkPipe>(ok_pipe)) 
		, nok_pipe_(std::forward<NokPipe>(nok_pipe)) 
	{}

    template<typename V>
    constexpr V process(const V& v) const noexcept
    {
		std::remove_cvref_t<V> oks{};
		std::remove_cvref_t<V> noks{};
		for (size_t i = 0; i < v.size(); i++) {
			if (std::invoke(p_, v[i]) == true)
				oks.push_back(v[i]);
			else
				noks.push_back(v[i]);
		}
		
		ok_pipe_.process(oks);
		nok_pipe_.process(noks);
		return v;
    }
};
	
template <typename P, concepts::Pipe OkPipe, concepts::Pipe2 NokPipe>
[[nodiscard]] constexpr
partition_t<P, OkPipe, NokPipe> partition(P&& p, OkPipe&& ok_pipe, NokPipe&& nok_pipe) noexcept
{
	return partition_t<P, OkPipe, NokPipe>(std::forward<P>(p),
										   std::forward<OkPipe>(ok_pipe),
										   std::forward<NokPipe>(nok_pipe));
}
	
template <typename P, concepts::Pipe OkPipe, concepts::Pipe2 NokPipe>
[[nodiscard]] constexpr
partition_t<P, OkPipe, NokPipe> partition(P&& p, OkPipe& ok_pipe, NokPipe& nok_pipe) noexcept
{
	return partition_t<P, OkPipe, NokPipe>(std::forward<P>(p), ok_pipe, nok_pipe);
}
	
}
