/** @file access.hpp
    @brief Access for private (or public) string conversion methods inside classes. */
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
#ifndef __STRINGIFY_ACCESS_HPP__
#define __STRINGIFY_ACCESS_HPP__

#ifndef STRINGIFY_TO_STRING_NAME
#define STRINGIFY_TO_STRING_NAME to_string
#endif

#include <stringify/string.hpp>
#include <stringify/detail/detection.hpp>

#include <utility>

namespace Stringify {

class Access {
	template<class T>
	using __access_to_string_function__ = decltype(std::declval<const T>(). STRINGIFY_TO_STRING_NAME ());

	template<class T>
	using __access_operator_string__ = decltype(String(std::declval<const T>()));

	template<class T>
	static constexpr bool __t_has_to_string__() {
		return detail::detection::is_detected<__access_to_string_function__, T>::value;
	}

	template<class T>
	static constexpr bool __t_has_operator_string__() {
		return detail::detection::is_detected<__access_operator_string__, T>::value;
	}
public:
	Access() = delete;
	~Access() = delete;

	template<class T>
	static constexpr bool type_t_has_to_string_function() {
		return __t_has_to_string__<T>();
	}

	template<class T>
	static constexpr bool type_t_has_operator_string() {
		return __t_has_operator_string__<T>();
	}

	template<class T>
	static inline String __object_to_string__(const T &object) {
		return object.STRINGIFY_TO_STRING_NAME();
	}

	template<class T>
	static inline String __object_string_operator__(const T &object) {
		return String(object);
	}
};

}

#endif