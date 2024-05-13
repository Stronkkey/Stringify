/** @file chrono.hpp
    @brief String conversion methods for types provided in \<chrono>. */
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
#ifndef __STRINGIFY_CHRONO_HPP__
#define __STRINGIFY_CHRONO_HPP__

#include <stringify/detail/convert_type.hpp>

#include <chrono>
#include <iomanip>

namespace Stringify {

/**
* @brief Puts the time into the stream.
* @see https://en.cppreference.com/w/cpp/io/manip/put_time.
*/
inline void time_t_into_stream(std::ostream &stream, const std::time_t &time, const char *format = "%c") {
	stream << std::put_time(std::localtime(&time), format);
}

/**
* @brief Puts the time point into the stream.
* @see time_t_into_stream.
*/
template<class Clock, class Duration>
void chrono_time_point_into_stream(std::ostream &stream, const std::chrono::time_point<Clock, Duration> &time_point, const char *format = "%c") {
	time_t_into_stream(stream, std::chrono::system_clock::to_time_t(time_point), format);
}

namespace detail {

template<class Rep, class Period>
struct convert_type<std::chrono::duration<Rep, Period>> {
	void operator()(std::ostream &stream, const std::chrono::duration<Rep, Period> &duration) {
		stream << static_cast<double>(duration.count()) / Period::den;
		stream << 's';
	}
};

template<class Clock, class Duration>
struct convert_type<std::chrono::time_point<Clock, Duration>> {
	void operator()(std::ostream &stream, const std::chrono::time_point<Clock, Duration> &time_point) {
		chrono_time_point_into_stream(stream, time_point);
	}
};

}

}

#endif
