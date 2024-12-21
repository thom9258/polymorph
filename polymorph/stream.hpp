#pragma once

#include "types.hpp"


namespace polymorph
{
	
template <typename Seperator, typename Ender>
class stream_t : public traits::pipe_tag
{
	std::ostream& os_;
	Seperator seperator_;
	Ender ender_;

public:
	explicit stream_t(std::ostream& os, Seperator&& seperator, Ender&& ender) 
		: os_(os)
		, seperator_(std::forward<Seperator>(seperator))
		, ender_(std::forward<Ender>(ender))
	{}

    template<typename V>
    constexpr auto process(const V& v) const noexcept
		-> void
    {
		for (size_t i = 0; i < v.size(); i++) {
			if (i < v.size() - 1)
				os_ << v[i] << seperator_;
			else
				os_ << v[i];
		}

		os_ << ender_;
    }
};
	
template <typename Seperator, typename Ender>
[[nodiscard]] constexpr
stream_t<Seperator, Ender>
stream(std::ostream& os, Seperator&& seperator, Ender&& ender) noexcept
{
	return stream_t<Seperator, Ender>(os, 
										 std::forward<Seperator>(seperator),
										 std::forward<Ender>(ender));
}
	
template <typename Seperator>
[[nodiscard]] constexpr
stream_t<Seperator, decltype("")>
stream(std::ostream& os, Seperator&& seperator) noexcept
{
	return stream_t<Seperator, decltype("")>(os, 
												std::forward<Seperator>(seperator),
												std::forward<decltype("")>(""));
}

}	
