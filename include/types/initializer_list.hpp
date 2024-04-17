#ifndef __STRINGIFY_INITIALIZER_LIST_HPP__
#define __STRINGIFY_INITIALIZER_LIST_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <include/detail/inline_to_string.hpp>
#include <include/partial_to_string.hpp>

#include <initializer_list>

namespace Stringify {

template<class T>
String to_string(const std::initializer_list<T> &initializer_list) {
	return detail::__to_string_generic_iterator_container__(initializer_list);
}

template<class T>
String to_strings(const std::initializer_list<T> &initializer_list) {
	return to_string(initializer_list);
}

};

#endif