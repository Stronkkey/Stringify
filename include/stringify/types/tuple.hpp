/** @file tuple.hpp
    @brief String conversion methods for types provided in <tuple>. */
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

#include <stringify/partial_to_string.hpp>

#include <tuple>

namespace Stringify {

namespace detail {

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type __tuple_for_each__(const std::tuple<Tp...> &, FuncT) {
}

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type __tuple_for_each__(const std::tuple<Tp...>& t, FuncT f) {
	f(std::get<I>(t));
	__tuple_for_each__<I + 1, FuncT, Tp...>(t, f);
}

}

template<class... Types>
String to_string_tuple(const std::tuple<Types...> &tuple) {
	String string = String();
	
	auto lambda = [&string](const auto &tuple_element) {
		string += to_string(tuple_element);
	};

	detail::__tuple_for_each__(tuple, lambda);
	return string;
}

template<class... Types>
String to_strings_tuple(const std::tuple<Types...> &tuple) {
	String string = String();
	
	auto lambda = [&string](const auto &tuple_element) {
		string += to_string(tuple_element) + ' ';
	};

	detail::__tuple_for_each__(tuple, lambda);
	return string;
}

template<class... Types>
std::array<String, sizeof...(Types)> tuple_to_string_array(const std::tuple<Types...> &tuple) {
	std::array<String, sizeof...(Types)> strings;
	size_t i = 0;
	
	auto lambda = [&i, &strings](const auto &tuple_element) {
		strings[i++] += to_string(tuple_element) + ' ';
	};

	detail::__tuple_for_each__(tuple, lambda);
	return strings;
}

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE1__(std::tuple, tuple, Types..., class... Types) {
	return to_string_tuple(tuple);
}

}

}

#endif