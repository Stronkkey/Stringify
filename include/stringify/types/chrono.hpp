/** @file chrono.hpp
    @brief String conversion methods for types provided in <chrono>. */
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

#include <stringify/detail/number_string_conversion.hpp>
#include <stringify/partial_to_string.hpp>

#include <chrono>

#include <iomanip>
#include <sstream>

namespace Stringify {

inline String to_string_time_t(const std::time_t &time, const std::locale &locale = std::locale(), const char *format = "%c") {
	std::basic_stringstream<String::value_type> string_stream = {};

	string_stream.imbue(locale);
	string_stream << std::put_time(std::localtime(&time), format);

	return string_stream.str();
}

template<class Clock, class Duration>
inline String time_point_chrono_to_string(const std::chrono::time_point<Clock, Duration> &time_point, const std::locale &locale = std::locale(), const char *format = "%c") {
	return to_string_time_t(std::chrono::system_clock::to_time_t(time_point), locale, format);
}

namespace detail {

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::chrono::duration, duration, Rep, class Rep, Period, class Period) {
	return detail::__to_string_number__(static_cast<double>(duration.count()) / Period::den) + 's';
}

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::chrono::time_point, time_point, Clock, class Clock, Duration, class Duration) {
	return time_point_chrono_to_string(time_point);
}

}

}

#endif