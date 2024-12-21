#pragma once

#include "detail.hpp"

namespace polymorph
{
	
class take_t : public traits::pipe_tag
{
	size_t count_;

public:
	explicit take_t(const size_t count) : count_(count) {}

    template<typename V>
    constexpr decltype(auto) process(const V& v) const noexcept
    {
		V out{};
		out.reserve(count_);
		const auto taking = (count_ < v.size()) ? count_ : v.size();
		for (size_t i = 0; i < taking; i++)
			out.push_back(v[i]);
        return out;
    }
};
	
[[nodiscard]] constexpr
take_t take(const size_t count) noexcept
{
	return take_t(count);
}
	
}
