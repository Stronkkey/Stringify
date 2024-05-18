/** @file partial_streaming.hpp
    @brief Partial definitions of streaming.hpp. */
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
#ifndef __STRINGIFY_PARTIAL_STREAMING_HPP__
#define __STRINGIFY_PARTIAL_STREAMING_HPP__

#include <iosfwd>

namespace Stringify {

template<class T>
constexpr bool is_streamable();

template<class T>
void write_into_stream(std::ostream &stream, const T &object);

template<class T, class... Args>
void write_into_stream(std::ostream &stream, const T &object, Args&&... args);

template<class T>
void write_into_streams(std::ostream &stream, const T &object);

template<class T, class... Args>
void write_into_streams(std::ostream &stream, const T &object, Args&&... args);

template<class T>
void write_into_streamn(std::ostream &stream, const T &object);

template<class T, class... Args>
void write_into_streamn(std::ostream &stream, const T &object, Args&&... args);

template<class T>
void write_into_streamsn(std::ostream &stream, const T &object);

template<class T, class... Args>
void write_into_streamsn(std::ostream &stream, const T &object, Args&&... args);


}

#endif