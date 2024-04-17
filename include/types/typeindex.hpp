#ifndef __STRINGIFY_TYPEINDEX_HPP__
#define __STRINGIFY_TYPEINDEX_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <include/detail/inline_to_string.hpp>
#include <include/partial_to_string.hpp>

#include <typeindex>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE__(std::type_info, type_info) {
	return type_info.name();
}

__STRINGIFY_DETAIL_TO_STRING_TYPE__(std::type_index, type_index) {
	return type_index.name();
}

}

}

#endif