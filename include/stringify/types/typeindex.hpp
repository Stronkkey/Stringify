/** @file typeindex.hpp
    @brief String conversion methods for types provided in \<typeindex>. */
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
#ifndef __STRINGIFY_TYPEINDEX_HPP__
#define __STRINGIFY_TYPEINDEX_HPP__

#include <stringify/detail/convert_type.hpp>

#include <ostream>
#include <typeindex>

namespace Stringify {

namespace detail {

template<>
struct convert_type<std::type_info> {
	void operator()(std::ostream &stream, const std::type_info &type_info) {
		stream << type_info.name();
	}
};

template<>
struct convert_type<std::type_index> {
	void operator()(std::ostream &stream, const std::type_index &type_index) {
		stream << type_index.name();
	}
};


}

}

#endif
