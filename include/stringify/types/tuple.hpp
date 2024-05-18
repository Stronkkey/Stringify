/** @file tuple.hpp
    @brief String conversion methods for types provided in \<tuple>. */
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
#ifndef __STRINGIFY_TUPLE_HPP__
#define __STRINGIFY_TUPLE_HPP__

#include <stringify/partial_streaming.hpp>
#include <stringify/detail/convert_type.hpp>

#include <tuple>
#include <ostream>

namespace Stringify {

namespace detail {

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type tuple_for_each(const std::tuple<Tp...> &, FuncT) {
}

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type tuple_for_each(const std::tuple<Tp...>& t, FuncT f) {
	f(std::get<I>(t));
	tuple_for_each<I + 1, FuncT, Tp...>(t, f);
}

template<class... Types>
struct convert_type<std::tuple<Types...>> {
	void operator()(std::ostream &stream, const std::tuple<Types...> &tuple) {
		stream << '{';
		size_t i = 0;
		const size_t goal = sizeof...(Types);
		auto lambda = [&stream, &i](const auto &tuple_element) {
			write_into_stream(stream, tuple_element);
			if (++i < sizeof...(Types))
				stream << ", ";
		};

		detail::tuple_for_each(tuple, lambda);
		stream << '}';
	}
};

}

}

#endif
