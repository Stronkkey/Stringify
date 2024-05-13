/** @file access.hpp
    @brief Access for private streaming methods inside classes. */
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
#ifndef __STRINGIFY_ACCESS_HPP__
#define __STRINGIFY_ACCESS_HPP__

#ifndef STRINGIFY_STREAMING_NAME
#define STRINGIFY_STREAMING_NAME write_into_s_stream
#endif 

#include <stringify/string.hpp>
#include <stringify/detail/detection.hpp>

#include <utility>

namespace Stringify {

/** 
* @brief A class that can be befriended to create private streaming methods within your own classes.
*/
class Access {
private:
	template<class T>
	using has_write_into_s_stream = decltype(std::declval<const T>().STRINGIFY_STREAMING_NAME(std::declval<std::ostream&>()));
public:
	Access() = delete;
	~Access() = delete;

	/**
	* @brief Returns true if T has the STRINGIFY_STREAMING_NAME function.
	*/
	template<class T>
	static constexpr bool __has_write_into_stream__() {
		return detail::detection::is_detected<has_write_into_s_stream, T>::value;
	}

	/**
	* @brief Equivalent to object.STRINGIFY_STREAMING_NAME(stream).
	* @note No checks are performed if the call is valid.
	*/
	template<class T>
	static void __write_into_stream__(std::ostream &stream, const T &object) {
		object.STRINGIFY_STREAMING_NAME(stream);
	}
};

}

#endif