#pragma once

#include "detail.hpp"
#include "utils.hpp"

#include <tuple>

namespace polymorph
{

template <concepts::Collection C>
class fuse1_t : public traits::pipe_tag
{
	C& c_;

public:
	explicit fuse1_t(C& c) : c_(c) {}

    template<typename V>
    constexpr decltype(auto) process(const V& v) const noexcept
    {
		std::vector<std::tuple<typename V::value_type, typename C::value_type>> out{};
		const auto size = v.size() < c_.size() ? v.size() : c_.size();
		utils::collection_reserve_additional(out, size);
		for (size_t i = 0; i < size; i++)
			out.emplace_back(v[i], c_[i]);

        return out;
    }
};
	
template <concepts::Collection C>
[[nodiscard]] constexpr
fuse1_t<C> fuse1(C& c) noexcept {

	return fuse1_t<C>(c);
}
	

template <concepts::Collection C1, concepts::Collection C2>
class fuse2_t : public traits::pipe_tag
{
	C1& c1_;
	C2& c2_;

public:
	explicit fuse2_t(C1& c1, C2& c2) : c1_(c1), c2_(c2) {}

    template<typename V>
    constexpr decltype(auto) process(const V& v) const noexcept
    {
		std::vector<std::tuple<typename V::value_type,
							   typename C1::value_type,
							   typename C2::value_type>> out{};
		const size_t _size = c1_.size() < c2_.size() ? c1_.size() : c2_.size();
		const size_t size = v.size() < _size ? v.size() : _size;
		utils::collection_reserve_additional(out, size);
		for (size_t i = 0; i < size; i++)
			out.emplace_back(v[i], c1_[i], c2_[i]);

        return out;
    }
};
	
template <concepts::Collection C1, concepts::Collection C2>
[[nodiscard]] constexpr
fuse2_t<C1, C2> fuse2(C1& c1, C2& c2) noexcept {

	return fuse2_t<C1, C2>(c1, c2);
}

}
