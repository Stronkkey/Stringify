#ifndef __STRINGIFY_INLINE_TO_STRING_HPP__
#define __STRINGIFY_INLINE_TO_STRING_HPP__

#include <include/string.hpp>

namespace Stringify {

namespace detail {

#define __STRINGIFY_DETAIL_TO_STRING_TYPE__(type, variant_arg_name) \
template<> \
struct __inline_to_string__<type> { \
	static const bool defined = true; \
	inline static String __to_string__(const type &variant); \
}; \
\
inline String __inline_to_string__<type>::__to_string__(const type & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE1__(type, variant_arg_name, template_name, template_parameter) \
template<template_parameter> \
struct __inline_to_string__<type<template_name>> { \
	static const bool defined = true; \
	inline static String __to_string__(const type<template_name> &variant); \
}; \
\
template<template_parameter>\
inline String __inline_to_string__<type<template_name>>::__to_string__(const type<template_name> & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE2__(type, variant_arg_name, template_name1, template_parameter1, template_name2, template_parameter2) \
template<template_parameter1, template_parameter2> \
struct __inline_to_string__<type<template_name1, template_name2>> { \
	static const bool defined = true; \
	inline static String __to_string__(const type<template_name1, template_name2> &variant); \
}; \
\
template<template_parameter1, template_parameter2>\
inline String __inline_to_string__<type<template_name1, template_name2>>::__to_string__(const type<template_name1, template_name2> & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE3__(type, variant_arg_name, template_name1, template_parameter1, template_name2, template_parameter2, template_name3, template_parameter3) \
template<template_parameter1, template_parameter2, template_parameter3> \
struct __inline_to_string__<type<template_name1, template_name2, template_name3>> { \
	static const bool defined = true; \
	inline static String __to_string__(const type<template_name1, template_name2, template_name3> &variant); \
}; \
\
template<template_parameter1, template_parameter2, template_parameter3>\
inline String __inline_to_string__<type<template_name1, template_name2, template_name3>>::__to_string__(const type<template_name1, template_name2, template_name3> & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE4__(type, variant_arg_name, template_name1, template_parameter1, template_name2, template_parameter2, template_name3, template_parameter3, template_name4, template_parameter4) \
template<template_parameter1, template_parameter2, template_parameter3, template_parameter4> \
struct __inline_to_string__<type<template_name1, template_name2, template_name3, template_name4>> { \
	static const bool defined = true; \
	inline static String __to_string__(const type<template_name1, template_name2, template_name3, template_name4> &variant); \
}; \
\
template<template_parameter1, template_parameter2, template_parameter3, template_parameter4>\
inline String __inline_to_string__<type<template_name1, template_name2, template_name3, template_name4>>::__to_string__(const type<template_name1, template_name2, template_name3, template_name4> & variant_arg_name)


#define __STRINGIFY_DETAIL_TO_STRING_TYPE_TEMPLATE5__(type, variant_arg_name, template_name1, template_parameter1, template_name2, template_parameter2, template_name3, template_parameter3, template_name4, template_parameter4, template_name5, template_parameter5) \
template<template_parameter1, template_parameter2, template_parameter3, template_parameter4, template_parameter5> \
struct __inline_to_string__<type<template_name1, template_name2, template_name3, template_name4, template_name5>> { \
	static const bool defined = true; \
	inline static String __to_string__(const type<template_name1, template_name2, template_name3, template_name4, template_name5> &variant); \
}; \
\
template<template_parameter1, template_parameter2, template_parameter3, template_parameter4, template_parameter5>\
inline String __inline_to_string__<type<template_name1, template_name2, template_name3, template_name4, template_name5>>::__to_string__(const type<template_name1, template_name2, template_name3, template_name4, template_name5> & variant_arg_name)

template<class T>
struct __inline_to_string__ {
	constexpr static bool defined = false;

	static inline String __to_string__(const T&) {
		return {};
	}
};

template<class T>
constexpr bool __is_inline_to_string_defined__() {
	return __inline_to_string__<T>::defined;
}

}

}

#endif