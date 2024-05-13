/** @file streaming.hpp
    @brief Methods to stream object into streams. */
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
#ifndef __STRINGIFY_STREAMING_HPP__
#define __STRINGIFY_STREAMING_HPP__

#include <stringify/detail/convert_type.hpp>
#include <stringify/detail/container_streaming.hpp>
#include <stringify/access.hpp>

#define S_WRITE_INTO_STREAM(...) ::Stringify::write_into_stream(__VA_ARGS__)
#define S_WRITE_INTO_STREAMS(...) ::Stringify::write_into_streams(__VA_ARGS__)
#define S_WRITE_INTO_STREAMN(...) ::Stringify::write_into_streamn(__VA_ARGS__)
#define S_WRITE_INTO_STREAMSN(...) ::Stringify::write_into_streamsn(__VA_ARGS__)


namespace Stringify {

namespace detail {

enum class ConversionOption {
	NONE,
	ARRAY,
	CONVERT_TYPE,
	OPERATOR_INTO,
	WRITE_INTO_STREAM
};

template<class T>
constexpr bool is_char_type() {
	return std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_all_extents<T>::type>::type>::type, char>::value;
}

template<class T>
using __operator_into__ = decltype(std::declval<std::ostream>() << std::declval<const T>());

template<class T>
constexpr bool has_operator_into() {
	return detection::is_detected<__operator_into__, T>::value;
}

template<class T>
constexpr ConversionOption get_conversion_option() {
	if (std::is_array<T>::value && !is_char_type<T>())
		return ConversionOption::ARRAY;

	if (has_operator_into<T>())
		return ConversionOption::OPERATOR_INTO;

	if (Access::__has_write_into_stream__<T>())
		return ConversionOption::WRITE_INTO_STREAM;

	if (is_convert_type_valid<T>())
		return ConversionOption::CONVERT_TYPE;

	return ConversionOption::NONE;
}

}

/**
* @returns true if the type T can be converted to a string.
*/
template<class T>
constexpr bool is_streamable() {
	return detail::get_conversion_option<T>() != detail::ConversionOption::NONE;
}

namespace detail {

enum class StreamWriterModifiers {
	NONE,
	SPACE,
	NOTHROW,
	SPACE_NOTHROW,
};

template<StreamWriterModifiers Mod = StreamWriterModifiers::NONE>
struct stream_writer {
	std::ostream &stream;
	unsigned int goal;
	unsigned int index;

	constexpr stream_writer(std::ostream &stream) : stream(stream) {
	}

	template<StreamWriterModifiers _Mod, class T, typename std::enable_if<_Mod == StreamWriterModifiers::NONE, bool>::type = true>
	void write_mod(const T &object) {
		write_into_stream(stream, object);
	}

	template<StreamWriterModifiers _Mod, class T, typename std::enable_if<_Mod == StreamWriterModifiers::SPACE, bool>::type = true>
	void write_mod(const T &object) {
		write_into_stream(stream, object);

		if (index < goal)
			stream << ' ';
	}

	template<StreamWriterModifiers _Mod, class T, typename std::enable_if<_Mod == StreamWriterModifiers::NOTHROW, bool>::type = true>
	void write_mod(const T &object) {
		write_into_streamn(stream, object);
	}

	template<StreamWriterModifiers _Mod, class T, typename std::enable_if<_Mod == StreamWriterModifiers::SPACE_NOTHROW, bool>::type = true>
	void write_mod(const T &object) {
		write_into_streamn(stream, object);

		if (index < goal)
			stream << ' ';
	}

	template<class T>
	stream_writer &operator<<(const T &object) {
		index++;
		if (!is_streamable<T>())
			return *this;

		write_mod<Mod, T>(object);
		return *this;
	}

	#if __cplusplus >= 201703L

	template<class T, class... Args>
	void write(const T &object, Args&&... args) {
		goal = 1 + sizeof...(Args);
		index = 1;

		(*this) << object;
		((*this) << ... << args);
	}

	#else

	template<class T>
	void write(const T &object) {
		(*this) << object;
	}

	template<class T, class... Args>
	void write(const T &object, Args&&... args) {
		goal = 1 + sizeof...(Args);
		index = 1;
	
		(*this) << object;
		write(args...);
	}

	#endif
};

template<StreamWriterModifiers Mod, class T, class... Args>
void vararg_into_stream(std::ostream &stream, const T &object, Args&&... args) {
	stream_writer<Mod> writer = stream;
	writer.write(object, args...);
}

}

namespace detail {

template<class T, typename std::enable_if<get_conversion_option<T>() == ConversionOption::NONE, bool>::type = true>
void write_to_stream_option(std::ostream&, const T&) {
}

template<class T, typename std::enable_if<get_conversion_option<T>() == ConversionOption::ARRAY, bool>::type = true>
void write_to_stream_option(std::ostream &stream, const T &object) {
	stream_array(stream, object);
}

template<class T, typename std::enable_if<get_conversion_option<T>() == ConversionOption::CONVERT_TYPE, bool>::type = true>
void write_to_stream_option(std::ostream &stream, const T &object) {
	convert_type<T>()(stream, object);
}

template<class T, typename std::enable_if<get_conversion_option<T>() == ConversionOption::OPERATOR_INTO, bool>::type = true>
void write_to_stream_option(std::ostream &stream, const T &object) {
	stream << object;
}

template<class T, typename std::enable_if<get_conversion_option<T>() == ConversionOption::WRITE_INTO_STREAM, bool>::type = true>
void write_to_stream_option(std::ostream &stream, const T &object) {
	Access::__write_into_stream__(stream, object);
}

template<class T>
void object_into_stream(std::ostream &stream, const T &object) {
	write_to_stream_option(stream, object);
}

}

template<class T>
void write_into_stream(std::ostream &stream, const T &object) {
	static_assert(is_streamable<T>(), "Can't stream object into stream.");
	detail::object_into_stream(stream, object);
}

template<class T, class... Args>
void write_into_stream(std::ostream &stream, const T &object, Args&&... args) {
	detail::vararg_into_stream<detail::StreamWriterModifiers::NONE>(stream, object, args...);
}

template<class T>
void write_into_streams(std::ostream &stream, const T &object) {
	write_into_stream(stream, object);
}

template<class T, class... Args>
void write_into_streams(std::ostream &stream, const T &object, Args&&... args) {
	detail::vararg_into_stream<detail::StreamWriterModifiers::SPACE>(stream, object, args...);
}

template<class T>
void write_into_streamn(std::ostream &stream, const T &object) {
	detail::object_into_stream(stream, object);
}

template<class T, class... Args>
void write_into_streamn(std::ostream &stream, const T &object, Args&&... args) {
	detail::vararg_into_stream<detail::StreamWriterModifiers::NOTHROW>(stream, object, args...);
}

template<class T>
void write_into_streamsn(std::ostream &stream, const T &object) {
	detail::object_into_stream(stream, object);
}

template<class T, class... Args>
void write_into_streamsn(std::ostream &stream, const T &object, Args&&... args) {
	detail::vararg_into_stream<detail::StreamWriterModifiers::SPACE_NOTHROW>(stream, object, args...);
}

};

#endif
