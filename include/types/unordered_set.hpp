#ifndef __STRINGIFY_UNORDERED_SET_HPP__
#define __STRINGIFY_UNORDERED_SET_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <include/detail/inline_to_string.hpp>
#include <include/partial_to_string.hpp>

#include <unordered_set>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE4__(std::unordered_set, unordered_set, Value, class Value, Hash, class Hash, Pred, class Pred, Allocator, class Allocator) {
	return __to_string_generic_index_container__(unordered_set);
}

}

}

#endif