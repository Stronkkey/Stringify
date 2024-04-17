#ifndef __STRINGIFY_FORWARD_LIST_HPP__
#define __STRINGIFY_FORWARD_LIST_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <include/detail/inline_to_string.hpp>
#include <include/partial_to_string.hpp>

#include <forward_list>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::forward_list, forward_list, T, class T, Allocator, class Allocator) {
	return __to_string_generic_iterator_container__(forward_list);
}

}

}

#endif