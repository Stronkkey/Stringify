#ifndef __STRINGIFY_TUPLE_HPP__
#define __STRINGIFY_TUPLE_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <stringify/detail/inline_to_string.hpp>

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