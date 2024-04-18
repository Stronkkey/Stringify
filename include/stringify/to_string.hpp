#ifndef __STRINGIFY_TO_STRING_HPP__
#define __STRINGIFY_TO_STRING_HPP__

#include <stringify/detail/string_conversion.hpp>
#include <stringify/access.hpp>

#define S_TO_STRING(...) ::Stringify::to_string(__VA_ARGS__)
#define S_TO_STRINGS(...) ::Stringify::to_strings(__VA_ARGS__)

namespace Stringify {

namespace detail {

template<bool>
struct __conditional_reinterpret_cast__;

template<>
struct __conditional_reinterpret_cast__<false> {
	template<class T>
	static uintptr_t __reinterpret__(const T&) {
		return 0;
	}
};

template<>
struct __conditional_reinterpret_cast__<true> {
	template<class T>
	static uintptr_t __reinterpret__(const T &t) {
		return reinterpret_cast<uintptr_t>(t);
	}
};

template<bool>
struct __call_to_string__;

template<>
struct __call_to_string__<false> {
	template<class T>
	static inline String __get_string__(const T&) {
		return {};
	}
};

template<>
struct __call_to_string__<true> {
	template<class T>
	static inline String __get_string__(const T &object) {
		return Access::__object_to_string__(object);
	}
};

}

/**
* Tries to convert the object into a string.
* This function succedes if any one of these requirements are met. 
* 1. T is char[] or char[N].
* 2. T is a pointer type.
* 3. T can be converted to the String type implicitly.
* An error is generated if none of the requirements could be met.
*/
template<class T>
inline String to_string(const T &object) {
	static_assert(detail::__can_t_be_converted_to_string__<T>(), "Cannot convert type T to a String.");

	if (std::is_array<T>::value)
		return detail::__string_array__<T>::__get_string__(object);

	if (std::is_pointer<T>::value)
		return detail::__to_string_int_hex__(detail::__conditional_reinterpret_cast__<std::is_pointer<T>::value>::__reinterpret__(object));

	if (Access::type_t_has_to_string_function<T>())
		return detail::__call_to_string__<Access::type_t_has_to_string_function<T>()>::__get_string__(object);

	if (Access::type_t_has_operator_string<T>())
		return detail::__explicitly_convertible_to_string__<Access::type_t_has_operator_string<T>()>::__convert_to_string__(object);

	if (detail::__is_inline_to_string_defined__<T>())
		return detail::__inline_to_string__<T>::__to_string__(object);

	return detail::__inline_to_string__<T>::__to_string__(object);
}

inline String to_string(signed char number) {
	return detail::__to_string_signed_number__(number);
}

inline String to_string(unsigned char number) {
	return detail::__to_string_unsigned_number__(number);
}

inline String to_string(short number) {
	return detail::__to_string_signed_number__(number);
}

inline String to_string(unsigned short number) {
	return detail::__to_string_unsigned_number__(number);
}

inline String to_string(int number) {
	return detail::__to_string_signed_number__(number);
}

inline String to_string(unsigned int number) {
	return detail::__to_string_unsigned_number__(number);
}

inline String to_string(long number) {
	return detail::__to_string_signed_number__(number);
}

inline String to_string(unsigned long number) {
	return detail::__to_string_unsigned_number__(number);
}

inline String to_string(long long number) {
	return detail::__to_string_signed_number__(number);
}

inline String to_string(unsigned long long number) {
	return detail::__to_string_unsigned_number__(number);
}

inline String to_string(float number) {
	return detail::__to_string_float_number__(number);
}

inline String to_string(double number) {
	return detail::__to_string_float_number__(number);
}

inline String to_string(long double number) {
	return detail::__to_string_float_number__(number);
}

inline String to_string(bool boolean) {
	return boolean ? "true" : "false";
}

inline String to_string(char character) {
	return String(&character, 1);
}

inline String to_string(char *string) {
	return String(string);
}

inline String to_string(const char *string) {
	return String(string);
}

template<class IntegerType>
inline String to_string_hex_integer(IntegerType integer) {
	static_assert(std::is_integral<IntegerType>::value, "IntegerType is not an integral type.");

	if (integer < 0)
		return detail::__to_string_int_hex__(static_cast<typename std::make_unsigned<IntegerType>::type>(integer));

	return detail::__to_string_int_hex__(integer);
}

template<class T, class... Args>
inline String to_string(const T &object, const Args&... args) {
	return detail::__get_vararg_string__(object, args...);
}

template<class T>
inline String to_strings(const T &object) {
	return to_string(object);
}

template<class T, class... Args>
inline String to_strings(const T &object, const Args&... args) {
	return detail::__get_vararg_strings__(object, args...);
}

};

#endif