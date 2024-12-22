#pragma once

#include "detail.hpp"
#include <iostream>

namespace polymorph
{
	
class take_t : public traits::pipe_tag
{
	size_t count_;

public:
	explicit take_t(const size_t count) : count_(count) {}

    template<typename V>
    auto process(const V& v) const noexcept
		-> std::remove_cvref_t<V>
    {
		std::remove_cvref_t<V> out{};
		const size_t take_count = (count_ < v.size()) ? count_ : v.size();
		std::cout << "taking: " << take_count << std::endl;
		out.reserve(take_count);
		for (size_t i = 0; i < take_count; i++)
			out.push_back(v[i]);
        return out;
    }
};
	
[[nodiscard]]
take_t take(const size_t count) noexcept
{
	return take_t(count);
}
	
}
