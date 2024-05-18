/** @file utility.hpp
    @brief String conversion methods for types provided in \<utility>. */
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

#include <stringify/detail/container_streaming.hpp>
#include <stringify/detail/convert_type.hpp>

#include <utility>
#include <ostream>

namespace Stringify {

namespace detail {

template<class T1, class T2>
struct convert_type<std::pair<T1, T2>> {
	void operator()(std::ostream &stream, const std::pair<T1, T2> &pair) {
		stream << '{';
		write_into_stream(stream, pair.first);
		stream << ", ";
		write_into_stream(stream, pair.second);
		stream << '}';
	}
};

template<class T>
struct convert_type<std::integer_sequence<T>> {
	void operator()(std::ostream &stream, const std::integer_sequence<T>&) {
		stream << "{}";
	}
};

template<class T, T... Ints>
struct convert_type<std::integer_sequence<T, Ints...>> {
	void operator()(std::ostream &stream, const std::integer_sequence<T, Ints...>&) {
		T array[sizeof...(Ints)] = {Ints...};
		stream_index_container(stream, array, sizeof...(Ints));
	}
};

}

}

#endif
