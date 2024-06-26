/** @file forward_list.hpp
    @brief String conversion methods for types provided in \<forward_list>. */
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
#ifndef __STRINGIFY_FORWARD_LIST_HPP__
#define __STRINGIFY_FORWARD_LIST_HPP__

#include <stringify/detail/convert_type.hpp>
#include <stringify/detail/container_streaming.hpp>

#include <forward_list>

namespace Stringify {

namespace detail {

template<class T, class Allocator>
struct convert_type<std::forward_list<T, Allocator>> {
	void operator()(std::ostream &stream, const std::forward_list<T, Allocator> &forward_list) {
		size_t i = 0;
		size_t container_size = std::distance(forward_list.begin(), forward_list.end());
		stream << '{';

		for (const auto &iterator: forward_list) {
			write_into_stream(stream, iterator);

			if (++i < container_size)
				stream << ", ";
		}

		stream << '}';
	}
};

}

}

#endif
