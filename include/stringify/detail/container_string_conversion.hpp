/** @file container_string_conversion.hpp
    @brief String conversion methods for generic container types and c-style arrays. */
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
#ifndef __STRINGIFY_CONTAINER_STRING_CONVERSION_HPP__
#define __STRINGIFY_CONTAINER_STRING_CONVERSION_HPP__

#include <stringify/partial_to_string.hpp>

namespace Stringify {

namespace detail {

template<class T>
struct __remove_array_qf__;

template<class T>
struct __remove_array_qf__ {
	using value_type = T;
};

template<class T>
struct __remove_array_qf__<T[]> {
	using value_type = T;
};

template<class T, size_t N>
struct __remove_array_qf__<T[N]> {
	using value_type = T;
};

template<class T, size_t N>
struct __remove_array_qf__<T[][N]> {
	using value_type = typename __remove_array_qf__<T>::value_type;
};

template<class T, size_t N, size_t N2>
struct __remove_array_qf__<T[N][N2]> {
	using value_type = typename __remove_array_qf__<T>::value_type;
};

template<class T, typename std::enable_if<!std::is_array<T>::value, bool>::type = true>
inline String __array_to_string__(const T &object) {
	return to_string(object);
}

template<class T, typename std::enable_if<std::is_array<T>::value, bool>::type = true>
inline String __array_to_string__(const T &array) {
	size_t element_count = sizeof(T) / sizeof(decltype(array[0]));
		Stringify::String str = "{";

		for (size_t i = 0; i < element_count; i++)
			str += __array_to_string__(array[i]) + ", ";

		str.resize(str.size() - 1);
		str[str.size() - 1] = '}';

		return str;

}

template<class Container>
inline String __to_string_iterator_container__(const Container &container) {
	String string = "{";

	for (const auto &element: container)
		string += to_string(element) + ", ";

	string.resize(string.size() - 1);
	string[string.size() - 1] = '}';

	return string;
}

template<class Container>
inline String __to_string_index_container__(const Container &container, size_t container_size) {
	String string = "{";

	for (size_t i = 0; i < container_size; i++) {
		if ((i + 1) == container_size)
			string += to_string(container[i]);
		else
			string += to_string(container[i]) + ", ";
	}

	string += '}';

	return string;
}

inline String __quote_string__(const String &string) {
	size_t string_size = string.size() + 2;
	String string_copy;
	string_copy.resize(string_size);

	string_copy[0] = '\"';
	string_copy[string_size - 1] = '\"';
	string.copy(&string_copy[1], string.size());

	return string_copy;
}

template<class Container>
inline String __to_string_iterator_pair_container__(const Container &container) {
	String string = "{";

	for (const auto &iterator: container)
		string += __quote_string__(to_string(iterator.first)) + ": " + __quote_string__(to_string(iterator.second)) + ", ";

	string.resize(string.size() - 1);
	string[string.size() - 1] = '}';

	return string;
}


}

}

#endif