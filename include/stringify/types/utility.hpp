/** @file utility.hpp
    @brief String conversion methods for types provided in <utility>. */
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
#ifndef __STRINGIFY_UTILITY_HPP__
#define __STRINGIFY_UTILITY_HPP__

#include <stringify/partial_to_string.hpp>

#include <utility>

namespace Stringify {

namespace detail {

template<size_t>
struct __integer_sequence_to_string__;

template<>
struct __integer_sequence_to_string__<0> {
	template<class T, T... Ints>
	static String __get_string__(const std::integer_sequence<T, Ints...>&) {
		return "{}";
	}
};

template<size_t size>
struct __integer_sequence_to_string__ {
	template<class T, T... Ints>
	static String __get_string__(const std::integer_sequence<T, Ints...>&) {
		T array[sizeof...(Ints) + 1] = {Ints...};
		return __to_string_index_container__(array, sizeof...(Ints));
	}
};

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::pair, pair, T1, class T1, T2, class T2) {
	return "{" + to_string(pair.first) + ", " + to_string(pair.second) + '}';
}

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::integer_sequence, integer_sequence, T, class T, Ints..., T... Ints) {
	return __integer_sequence_to_string__<sizeof...(Ints)>::__get_string__(integer_sequence);
}

}

}

#endif