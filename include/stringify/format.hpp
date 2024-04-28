/** @file format.hpp
    @brief Methods for formatting strings. */
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
#ifndef __STRINGIFY_FORMAT_HPP__
#define __STRINGIFY_FORMAT_HPP__

#include <stringify/to_string.hpp>

#include <array>

#define S_FORMAT(string, ...) ::Stringify::format(string, __VA_ARGS__)
#define S_VFORMAT(string, format_specifier, ...) ::Stringify::vformat(string, ::Stringify::args_to_string_array(__VA_ARGS__), format_specifier)

namespace Stringify {

namespace detail {

template<size_t N>
struct __op_string_array__ {
	std::array<String, N> array;
	size_t i;

	template<class T>
	__op_string_array__ &operator<<(const T &object) {
		array[i++] = to_string(object);
		return *this;
	}

	__op_string_array__ &operator<<(const String &string) {
		const char *c_string = string.data();
		array[i++] = String(c_string, string.size());
		return *this;
	}
};

template<size_t N, class T>
void __add_to_array__(__op_string_array__<N> &array, const T &object) {
	array << object;
}

template<size_t N, class T, class... Args>
void __add_to_array__(__op_string_array__<N> &array, const T &object, Args&&... args) {
	array << object;
	__add_to_array__(array, args...);
}

}

template<class T, class... Args>
std::array<String, sizeof...(Args) + 1> args_to_string_array(const T &t, Args&&... args) {
	detail::__op_string_array__<sizeof...(Args) + 1> string_array = {};
	string_array.i = 0;

	#if __cplusplus >= 201703L

	string_array << t;
	(string_array << ... << args);

	#else

	detail::__add_to_array__(string_array, t, args...);

	#endif

	return string_array.array;
}

template<class T>
inline std::array<String, 1> args_to_string_array(const T &object) {
	return {to_string(object)};
}

inline std::array<String, 0> args_to_string_array() {
	return {};
}

template<size_t N>
inline String vformat(const String &fmt, const std::array<String, N> &array, const String &format_specifier = "{}") {
	if (fmt.empty())
		return "";

	const size_t string_length = fmt.length();
	const size_t format_str_length = format_specifier.length();

	String str = String();
	size_t found_characters = String::npos;
	size_t occurence_count = 0;
	size_t last_occurence = 0;

	for (size_t pos = 0; pos < string_length; pos++) {
		char character = fmt[pos];

		if (occurence_count >= array.size())
			break;

		if (found_characters == String::npos && character == format_specifier.front()) {
			found_characters = 1;
			continue;
		}

		if (found_characters == String::npos)
			continue;

		if (character == format_specifier.at(found_characters))
			found_characters++;
		else {
		 	found_characters = String::npos;
			continue;
		}

		if (found_characters < format_str_length)
			continue;
		
		str += fmt.substr(last_occurence, pos - 1 - last_occurence);
		str += to_string(array.at(occurence_count));
		occurence_count++;
		last_occurence = pos + 1;
		found_characters = String::npos;
	}
	str += fmt.substr(last_occurence, string_length - last_occurence);

	return str;

}

template<class... Args>
inline String format(const String &format, Args&&... args) {
	return vformat(format, args_to_string_array(args...));
}

}

#endif