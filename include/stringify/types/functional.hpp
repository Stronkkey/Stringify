/** @file functional.hpp
    @brief String conversion methods for types provided in <functional>. */
/*
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <https://unlicense.org>	
*/
#ifndef __STRINGIFY_FUNCTIONAL_HPP__
#define __STRINGIFY_FUNCTIONAL_HPP__

#include <stringify/detail/number_string_conversion.hpp>
#include <stringify/partial_to_string.hpp>

#include <functional>

namespace Stringify {

namespace detail {

template<class R, class... ReturnType>
String __to_string_function__(const std::function<R(ReturnType...)> &function) {
	using sig_ptr = R(*)(ReturnType...);

	auto function_pointer = function.template target<sig_ptr>();
	return detail::__to_string_int_hex__(reinterpret_cast<uintptr_t>(*function_pointer));
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