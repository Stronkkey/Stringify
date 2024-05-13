/** @ingroup Internal
    @file convert_type.hpp
    @brief Streaming for defined types. */
/*
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <https://unlicense.org>	
*/

#ifndef __STRINGIFY_CONVERT_TYPE_HPP__
#define __STRINGIFY_CONVERT_TYPE_HPP__

#include <stringify/detail/detection.hpp>

#include <iosfwd>

namespace Stringify {

namespace detail {

/**
* @brief Object streaming for defined types.
* @details If a specialization of convert_type<T> is not provided by the program or the user, it is disabled.
* convert_type<T> is considered enabled if the following are all true:
* - @p std::is_default_constructible<convert_type<T>>::value
* - @p std::is_copy_constructible<convert_type<T>>::value
* - @p std::is_move_constructible<convert_type<T>>::value
* - @p std::is_copy_assignable<convert_type<T>>::value
* - @p std::is_move_assignable<convert_type<T>>::value
*
* Otherwise the specialization is considered disabled.
*/
template<class T>
struct convert_type {
	convert_type() = delete;

	/**
    * @brief Streams the object into the stream.
	* @details Enabled specializations of convert_type should define an @p operator() that takes 2 arguments:
	* - Stream with a type of @p std::ostream&
	* - Object with a type of @p T.
	*
	* Return type may be of any valid type (usually void).
	*/
	void operator()(std::ostream&, const T&) {
	}
};

template<class T>
using __convert_type_operator__ = decltype(convert_type<T>()(std::declval<std::ostream&>(), std::declval<const T&>()));

/**
* @brief Returns true if the type T can be streamed with convert_type<T>::operator().
*/
template<class T>
constexpr bool is_convert_type_valid() {
	return detection::is_detected<__convert_type_operator__, T>::value;
}

}

}

#endif