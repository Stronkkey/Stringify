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

/**
* @brief Equivalent to Stringify::vformat_stream.
*/
#define S_STREAM_VFORMAT(stream, fmt, format_specifier, ...) ::Stringify::vformat_stream(stream, fmt, ::Stringify::args_to_string_array(__VA_ARGS__), format_specifier)

/**
* @brief Equivalent to Stringify::format_stream.
*/
#define S_STREAM_FORMAT(stream, fmt, ...) ::Stringify::format_stream(stream, fmt, __VA_ARGS__)

/**
* @brief Equivalent to Stringify::format.
*/
#define S_FORMAT(string, ...) ::Stringify::format(string, __VA_ARGS__)

/**
* @brief Equivalent to Stringify::vformat.
*/
#define S_VFORMAT(string, format_specifier, ...) ::Stringify::vformat(string, ::Stringify::args_to_string_array(__VA_ARGS__), format_specifier)

namespace Stringify {

namespace detail {

/**
* @brief Wrapper for std::array<String, N>.
*/
template<size_t N>
struct string_array {
	std::array<String, N> array;
	size_t i;

	/**
	* @brief Calls to_string on the object argument and adds it to the array.
	*/
	template<class T>
	string_array &operator<<(const T &object) {
		array[i++] = to_string(object);
		return *this;
	}

	/**
	* @brief Adds the string to the array.
	*/
	string_array &operator<<(const String &string) {
		array[i++] = string;
		return *this;
	}
};

/**
* @brief Equivalent to std::operator<<(array, object).
*/
template<size_t N, class T>
void add_to_string_array(string_array<N> &array, const T &object) {
	array << object;
}

/**
* @brief Recursively calls add_to_string_array with the arguments.
*/
template<size_t N, class T, class... Args>
void add_to_string_array(string_array<N> &array, const T &object, Args&&... args) {
	array << object;
	add_to_string_array(array, args...);
}

}

/**
* @brief Converts the arguments to a string array.
*/
template<class T, class... Args>
std::array<String, sizeof...(Args) + 1> args_to_string_array(const T &object, Args&&... args) {
	detail::string_array<sizeof...(Args) + 1> string_array = {};
	string_array.i = 0;

	#if __cplusplus >= 201703L

	string_array << object;
	(string_array << ... << args);

	#else

	detail::__add_to_array__(string_array, t, args...);

	#endif

	return string_array.array;
}

/**
* @brief Adds the object to a 1 sized array.
*/
template<class T>
std::array<String, 1> args_to_string_array(const T &object) {
	return {to_string(object)};
}

/**
* @brief Creates an empty array.
*/
inline std::array<String, 0> args_to_string_array() {
	return {};
}

template<size_t N>
void vformat_stream(std::ostream &stream, const String &fmt, const std::array<String, N> &format_list, const String &format_specifier = "{}") {
	if (fmt.empty())
		return;

	if (format_specifier.empty()) {
		stream << fmt;
		return;
	}

	const size_t string_length = fmt.length();
	const size_t format_str_length = format_specifier.length();

	String::size_type found_characters = String::npos;
	size_t occurence_count = 0;
	size_t last_occurence = 0;

	for (size_t pos = 0; pos < string_length; pos++) {
		char character = fmt[pos];

		if (occurence_count >= format_list.size())
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
		
		stream << String(fmt.data() + last_occurence, pos - 1 - last_occurence);
		write_into_stream(stream, format_list.at(occurence_count));

		occurence_count++;
		last_occurence = pos + 1;
		found_characters = String::npos;
	}

	stream << String(fmt.data() + last_occurence, string_length - last_occurence);
}

template<class... Args>
void format_stream(std::ostream &stream, const String &fmt, Args&&... args) {
	vformat_stream(stream, fmt, args_to_string_array(args...));
}

template<size_t N>
String vformat(const String &fmt, const std::array<String, N> &array, const String &format_specifier = "{}") {
	std::basic_stringstream<String::value_type> string_stream = {};
	vformat_stream(string_stream, fmt, array, format_specifier);
	return string_stream.str();
}

template<class... Args>
String format(const String &fmt, Args&&... args) {
	std::basic_stringstream<String::value_type> string_stream = {};
	format_stream(string_stream, fmt, args...);
	return string_stream.str();
}

}

#endif
