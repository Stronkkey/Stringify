#ifndef __STRINGIFY_VECTOR_HPP__
#define __STRINGIFY_VECTOR_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <stringify/detail/inline_to_string.hpp>

#include <vector>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::vector, vector, T, class T, Allocator, class Allocator) {
	return __to_string_generic_iterator_container__(vector);
}

}

}

#endif