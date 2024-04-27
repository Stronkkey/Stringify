/** @file inline_to_string.hpp
    @brief Conversion interface for types provided directly in the library. */
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
#ifndef __STRINGIFY_INLINE_TO_STRING_HPP__
#define __STRINGIFY_INLINE_TO_STRING_HPP__

#include <stringify/string.hpp>

namespace Stringify {

namespace detail {

#define __STRINGIFY_DETAIL_TO_STRING_TYPE__(type, variant_arg_name) \
template<> \
struct __inline_to_string__<type> : std::true_type { \
	constexpr static bool cvref = true; \
	inline static String __to_string__(const type &variant); \
}; \
\
inline String __inline_to_string__<type>::__to_string__(const type & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE1__(type, variant_arg_name, template_name, template_parameter) \
template<template_parameter> \
struct __inline_to_string__<type<template_name>> : std::true_type { \
	constexpr static bool cvref = true; \
	inline static String __to_string__(const type<template_name> &variant); \
}; \
\
template<template_parameter>\
inline String __inline_to_string__<type<template_name>>::__to_string__(const type<template_name> & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(type, variant_arg_name, template_name1, template_parameter1, template_name2, template_parameter2) \
template<template_parameter1, template_parameter2> \
struct __inline_to_string__<type<template_name1, template_name2>> : std::true_type { \
	constexpr static bool cvref = true; \
	inline static String __to_string__(const type<template_name1, template_name2> &variant); \
}; \
\
template<template_parameter1, template_parameter2>\
inline String __inline_to_string__<type<template_name1, template_name2>>::__to_string__(const type<template_name1, template_name2> & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE3__(type, variant_arg_name, template_name1, template_parameter1, template_name2, template_parameter2, template_name3, template_parameter3) \
template<template_parameter1, template_parameter2, template_parameter3> \
struct __inline_to_string__<type<template_name1, template_name2, template_name3>> : std::true_type { \
	constexpr static bool cvref = true; \
	inline static String __to_string__(const type<template_name1, template_name2, template_name3> &variant); \
}; \
\
template<template_parameter1, template_parameter2, template_parameter3>\
inline String __inline_to_string__<type<template_name1, template_name2, template_name3>>::__to_string__(const type<template_name1, template_name2, template_name3> & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE4__(type, variant_arg_name, template_name1, template_parameter1, template_name2, template_parameter2, template_name3, template_parameter3, template_name4, template_parameter4) \
template<template_parameter1, template_parameter2, template_parameter3, template_parameter4> \
struct __inline_to_string__<type<template_name1, template_name2, template_name3, template_name4>> : std::true_type { \
	constexpr static bool cvref = true; \
	inline static String __to_string__(const type<template_name1, template_name2, template_name3, template_name4> &variant); \
}; \
\
template<template_parameter1, template_parameter2, template_parameter3, template_parameter4>\
inline String __inline_to_string__<type<template_name1, template_name2, template_name3, template_name4>>::__to_string__(const type<template_name1, template_name2, template_name3, template_name4> & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE5__(type, variant_arg_name, template_name1, template_parameter1, template_name2, template_parameter2, template_name3, template_parameter3, template_name4, template_parameter4, template_name5, template_parameter5) \
template<template_parameter1, template_parameter2, template_parameter3, template_parameter4, template_parameter5> \
struct __inline_to_string__<type<template_name1, template_name2, template_name3, template_name4, template_name5>> : std::true_type { \
	constexpr static bool cvref = true; \
	inline static String __to_string__(const type<template_name1, template_name2, template_name3, template_name4, template_name5> &variant); \
}; \
\
template<template_parameter1, template_parameter2, template_parameter3, template_parameter4, template_parameter5>\
inline String __inline_to_string__<type<template_name1, template_name2, template_name3, template_name4, template_name5>>::__to_string__(const type<template_name1, template_name2, template_name3, template_name4, template_name5> & variant_arg_name)

/**
* @brief structure, whose template type T can be specialized to create to_string functions.
* @note avoid specializing this struct directly, instead, use the __STRINGIFY_DETAIL_TO_STRING_TYPE__ macros to specialize it.
*/
template<class T>
struct __inline_to_string__ : std::false_type {
	constexpr static bool cvref = true;

	static inline String __to_string__(const T&) {
		return {};
	}
};

/**
* @brief Equivalent to __inline_to_string__<T>::value.
*/
template<class T>
constexpr bool __inline_to_string_defined__() {
	return __inline_to_string__<T>::value;
}

}

}

#endif