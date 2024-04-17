#ifndef __STRINGIFY_SET_HPP__
#define __STRINGIFY_SET_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <include/detail/inline_to_string.hpp>
#include <include/partial_to_string.hpp>

#include <set>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE3__(std::set, set, T, class T, Allocator, class Allocator, Compare, class Compare) {
	return __to_string_generic_iterator_container__(set);
}

}

}

#endif