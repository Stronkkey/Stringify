/** @file base_inline_string.hpp
    @brief String conversion methods for string and character types. */
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
#ifndef __STRINGIFY_BASE_INLINE_STRING_HPP__
#define __STRINGIFY_BASE_INLINE_STRING_HPP__

#include <stringify/detail/inline_to_string.hpp>

namespace Stringify {

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE__(char, character) {
	return String(1, character);
}

__STRINGIFY_DETAIL_TO_STRING_TYPE__(bool, boolean) {
	return boolean ? "true" : "false";
}

__STRINGIFY_DETAIL_TO_STRING_TYPE__(String, string) {
	return string;
}

template<>
struct __inline_to_string__<char*> : std::true_type {	
	static inline String __to_string__(char *string) {
		return String(reinterpret_cast<const char*>(string));
	}
};

template<>
struct __inline_to_string__<const char*> : std::true_type {	
	static inline String __to_string__(const char *string) {
		return String(string);
	}
};

}

}

#endif