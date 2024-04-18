#ifndef __STRINGIFY_ARRAY_HPP__
#define __STRINGIFY_ARRAY_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <stringify/detail/inline_to_string.hpp>

#include <array>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::array, array, T, class T, N, size_t N) {
	return __to_string_generic_index_container__(array, N);
}

}

}

#endif