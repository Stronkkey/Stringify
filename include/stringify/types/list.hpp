#ifndef __STRINGIFY_LIST_HPP__
#define __STRINGIFY_LIST_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <stringify/detail/inline_to_string.hpp>

#include <list>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::list, list, T, class T, Allocator, class Allocator) {
	return __to_string_generic_iterator_container__(list);
}

}

}

#endif