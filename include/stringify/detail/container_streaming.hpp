/** @ingroup Internal
    @file container_streaming.hpp
    @brief Streaming functions for c-arrays and generic container types. */
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
#ifndef __STRINGIFY_CONTAINER_STREAMING_HPP__
#define __STRINGIFY_CONTAINER_STREAMING_HPP__

#include <stringify/partial_streaming.hpp>

#include <ostream>

namespace Stringify {

namespace detail {

/**
* @brief Behaves like write_into_stream.
*/
template<class T, typename std::enable_if<!std::is_array<T>::value, bool>::type = true>
void stream_array(std::ostream &stream, const T &object) {
	write_into_stream(stream, object);
}

/**
* @brief Streams the c-array into the stream.
*/
template<class T, typename std::enable_if<std::is_array<T>::value, bool>::type = true>
void stream_array(std::ostream &stream, const T &array) {
	size_t element_count = sizeof(T) / sizeof(decltype(array[0]));
	stream << '{';

	for (size_t i = 0; i < element_count; i++) {
		stream_array(stream, array[i]);
		if ((i + 1) < element_count)
			stream << ", ";
	}

	stream << '}';
}

/**
* @brief Streams the container into the stream.
* @note The container type must meet the requirements of Container.
*/
template<class Container>
void stream_container(std::ostream &stream, const Container &container) {
	size_t i = 0;
	stream << '{';

	for (const auto &iterator: container) {
		write_into_stream(stream, iterator);

		if (++i < container.size())
			stream << ", ";
	}

	stream << '}';
}

/**
* @brief Streams the container into the stream.
* @note The container type must overload the member access [] operator.
*/
template<class Container>
inline void stream_index_container(std::ostream &stream, const Container &container, size_t container_size) {
	stream << '{';

	for (size_t i = 0; i < container_size; i++) {
		write_into_stream(stream, container[i]);
		if ((i + 1) < container_size)
			stream << ", ";
	}

	stream << '}';
}

/**
* @brief Streams the container into the stream.
* @note The container types iterator must provide a first and second member variable.
*/
template<class Container>
inline void stream_pair_container(std::ostream &stream, const Container &container) {
	size_t i = 0;
	stream << '{';

	for (const auto &iterator: container) {
		stream << '\"';
		write_into_stream(stream, iterator.first);
		stream << "\": \"";
		write_into_stream(stream, iterator.second);
		stream << '\"';

		if (++i < container.size())
			stream << ", ";
	}

	stream << '}';
}


}

}

#endif
