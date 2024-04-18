#ifndef __STRINGIFY_MAP_HPP__
#define __STRINGIFY_MAP_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include "../detail/inline_to_string.hpp"

#include <map>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE4__(std::map, map, Key, class Key, Value, class Value, Compare, class Compare, Allocator, class Allocator) {
	return __to_string_generic_iterator_pair_container__(map);
}

}

}

#endif