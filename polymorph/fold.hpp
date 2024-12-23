#pragma once

#include "detail.hpp"

namespace polymorph
{

template <typename Folder, typename Init>
class fold_left_t : public traits::pipe_tag
{
	Folder folder_;
	Init init_;

public:
	explicit fold_left_t(Folder&& folder, Init&& init) 
		: folder_(std::forward<Folder>(folder)) 
		, init_(std::forward<Init>(init)) 
	{}
	
	explicit fold_left_t(Folder&& folder, const Init& init) 
		: folder_(std::forward<Folder>(folder)) 
		, init_(init) 
	{}
	explicit fold_left_t(const Folder& folder, Init&& init) 
		: folder_(folder) 
		, init_(std::forward<Init>(init)) 
	{}

	explicit fold_left_t(const Folder& folder, const Init& init) 
		: folder_(folder) 
		, init_(init) 
	{}




    template<typename V>
    constexpr decltype(auto) process(const V& v) const noexcept
		//requires std::is_same<Value, V>
    {
		Init res = init_;
		for (size_t i = 0; i < v.size(); i++)
			res = std::invoke(folder_, res, v[i]);
        return res;
    }
};
	
template <typename Folder, typename Init>
[[nodiscard]] constexpr
fold_left_t<Folder, Init> fold_left(Folder&& folder, Init&& init) noexcept
{
	return fold_left_t<Folder, Init>(std::forward<Folder>(folder),
									 std::forward<Init>(init));
}
	
template <typename Folder, typename Init>
[[nodiscard]] constexpr
fold_left_t<Folder, Init> fold_left(const Folder& folder, const Init& init) noexcept
{
	return fold_left_t<Folder, Init>(folder, init);
}
	
template <typename Folder, typename Init>
[[nodiscard]] constexpr
fold_left_t<Folder, Init> fold_left(Folder&& folder, const Init& init) noexcept
{
	return fold_left_t<Folder, Init>(std::forward<Folder>(folder), init);
}
	
template <typename Folder, typename Init>
[[nodiscard]] constexpr
fold_left_t<Folder, Init> fold_left(const Folder& folder, Init&& init) noexcept
{
	return fold_left_t<Folder, Init>(folder, std::forward<Init>(init));
}

}	
