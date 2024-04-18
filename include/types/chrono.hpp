#ifndef __STRINGIFY_CHRONO_HPP__
#define __STRINGIFY_CHRONO_HPP__

#ifndef __STRINGIFY_TO_STRING_HPP__
#error Include stringify_to_string.hpp before including this file.
#endif

#include "../detail/inline_to_string.hpp"

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
	return to_string(static_cast<double>(duration.count()) / Period::den) + 's';
}

__STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(std::chrono::time_point, time_point, Clock, class Clock, Duration, class Duration) {
	return time_point_chrono_to_string(time_point);
}

}

}

#endif