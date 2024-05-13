/** @file memory.hpp
    @brief String conversion methods for types provided in \<memory>. */
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
#ifndef __STRINGIFY_MEMORY_HPP__
#define __STRINGIFY_MEMORY_HPP__

#include <stringify/detail/convert_type.hpp>

#include <ostream>
#include <memory>

namespace Stringify {

namespace detail {

template<class T>
struct convert_type<std::shared_ptr<T>> {
	void operator()(std::ostream &stream, const std::shared_ptr<T> &shared_ptr) {
		std::ios_base::fmtflags flags = stream.flags();
		stream << std::hex;
		stream << reinterpret_cast<uintptr_t>(shared_ptr.get());
		stream.setf(flags);
	}
};

template<class T>
struct convert_type<std::unique_ptr<T>> {
	void operator()(std::ostream &stream, const std::unique_ptr<T> &unique_ptr) {
		std::ios_base::fmtflags flags = stream.flags();
		stream << std::hex;
		stream << reinterpret_cast<uintptr_t>(unique_ptr.get());
		stream.setf(flags);
	}
};

template<class T>
struct convert_type<std::weak_ptr<T>> {
	void operator()(std::ostream &stream, const std::weak_ptr<T> &weak_ptr) {
		std::ios_base::fmtflags flags = stream.flags();
		stream << std::hex;
		if (!weak_ptr.expired())
			stream << reinterpret_cast<uintptr_t>(weak_ptr.lock().get());
		else
			stream << static_cast<uintptr_t>(0);
		stream.setf(flags);
	}
};

}

}

#endif
