/*! \file detection.hpp
    \brief Implementation of std::experimental::detected. */
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
#ifndef __STRINGIFY_IS_DETECTED_HPP__
#define __STRINGIFY_IS_DETECTED_HPP__

#include <type_traits>

namespace Stringify {

namespace detail {

// See https://en.cppreference.com/w/cpp/experimental/is_detected.

namespace detection {

template< class... >
using void_type = void;

struct nonesuch {
	~nonesuch() = delete;
	nonesuch(nonesuch const&) = delete;
	void operator=(nonesuch const&) = delete;
};

template<class Default, class AlwaysVoid, template<class...> class Op, class... Args>
struct __detector__ {
	using value_type = std::false_type;
	using type = Default;
};
 
template<class Default, template<class...> class Op, class... Args>
struct __detector__<Default, void_type<Op<Args...>>, Op, Args...> {
	using value_type = std::true_type;
	using type = Op<Args...>;
};
 
template<template<class...> class Op, class... Args>
using is_detected = typename __detector__<nonesuch, void, Op, Args...>::value_type;
 
template<template<class...> class Op, class... Args>
using detected_type = typename __detector__<nonesuch, void, Op, Args...>::type;
 
template<class Default, template<class...> class Op, class... Args>
using detected_or = __detector__<Default, void, Op, Args...>;


}

}

}

#endif