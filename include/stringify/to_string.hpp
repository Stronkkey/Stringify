/** @file to_string.hpp
    @brief Functions to convert objects into stream. */
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
#ifndef __STRINGIFY_TO_STRING_HPP__
#define __STRINGIFY_TO_STRING_HPP__

#include <stringify/streaming.hpp>

#include <sstream>

/**
* @brief Shortcut for Stringify::to_string.
*/
#define S_TO_STRING(...) ::Stringify::to_string(__VA_ARGS__)

/**
* @brief Shortcut for Stringify::to_strings.
*/
#define S_TO_STRINGS(...) ::Stringify::to_strings(__VA_ARGS__)

/**
* @brief Shortcut for Stringify::to_string_n.
*/
#define S_TO_STRING_N(...) ::Stringify::to_string_n(__VA_ARGS__)

/**
* @brief Shortcut for Stringify::to_strings_n.
*/
#define S_TO_STRINGS_N(...) ::Stringify::to_strings_n(__VA_ARGS__)

namespace Stringify {

/**
* @returns true if the type T can be converted to a string.
*/
template<class T>
constexpr bool is_convertable_to_string() {
	return is_streamable<T>();
}

/**
* @brief Converts the number into a Big-endianess hexidecimal string and returns it.
*/
template<class IntegerType, typename std::enable_if<std::is_integral<IntegerType>::value, bool>::type = true>
inline String to_string_hex_integer(IntegerType integer) {
	return (std::stringstream() << integer).str();
}

/**
* @brief Converts the objects into a string using S_WRITE_INTO_STREAM.
* @returns The objects converted to a string.
* @note An error is generated if any one of the objects cannot be converted to a string.
*/
template<class T, class... Args>
inline String to_string(const T &object, Args&&... args) {
	std::stringstream string_stream = {};
	S_WRITE_INTO_STREAM(string_stream, object, args...);
	return string_stream.str();
}

template<class T, class... Args>
inline String to_strings(const T &object, Args&&... args) {
	std::stringstream string_stream = {};
	S_WRITE_INTO_STREAMS(string_stream, object, args...);
	return string_stream.str();
}

template<class T, class... Args>
String to_string_n(const T &object, Args&&... args) {
	std::stringstream string_stream = {};
	S_WRITE_INTO_STREAMN(string_stream, object, args...);
	return string_stream.str();
}

/**
* @brief Converts the objects into strings.
* @brief Objects which cannot be conxverted are ignored and will be converted into an empty string.
* @returns the objects converted to a string.
* @see to_string
*/
template<class T, class... Args>
inline String to_strings_n(const T &object, Args&&... args) {
	std::stringstream string_stream = {};
	S_WRITE_INTO_STREAMSN(string_stream, object, args...);
	return string_stream.str();
}

};

#endif
