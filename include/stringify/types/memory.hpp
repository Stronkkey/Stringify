#ifndef __STRINGIFY_MEMORY_HPP__
#define __STRINGIFY_MEMORY_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <stringify/detail/inline_to_string.hpp>

#include <memory>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE1__(std::shared_ptr, shared_ptr, T, class T) {
	return to_string(shared_ptr.get());
}

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE1__(std::unique_ptr, unique_ptr, T, class T) {
	return to_string(unique_ptr.get());
}

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE1__(std::weak_ptr, weak_ptr, T, class T) {
	return to_string(weak_ptr.lock().get());
}

}

}

#endif