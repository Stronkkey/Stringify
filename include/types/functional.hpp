#ifndef __STRINGIFY_FUNCTIONAL_HPP__
#define __STRINGIFY_FUNCTIONAL_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include <include/detail/inline_to_string.hpp>
#include <include/partial_to_string.hpp>

#include <functional>

namespace Stringify {

namespace detail {

template<class R, class... ReturnType>
String __to_string_function__(const std::function<R(ReturnType...)> &function) {
	using sig_ptr = R(*)(ReturnType...);

	auto function_pointer = function.template target<sig_ptr>();
	return to_string(*function_pointer);
}

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE1__(std::function, function, Signature, class Signature) {
	return __to_string_function__(function);
}

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE1__(std::reference_wrapper, reference_wrapper, T, class T) {
	return to_string(reference_wrapper.get());
}

}

}

#endif