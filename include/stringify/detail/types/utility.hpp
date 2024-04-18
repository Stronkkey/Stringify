#ifndef __STRINGIFY_UTILITY_HPP__
#define __STRINGIFY_UTILITY_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include "../detail/inline_to_string.hpp"

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
		return __to_string_generic_index_container__(array, sizeof...(Ints));
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