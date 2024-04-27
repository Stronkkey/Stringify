#ifndef __STRINGIFY_TO_STRING_HPP__
#define __STRINGIFY_TO_STRING_HPP__

#include <stringify/detail/string_conversion.hpp>
#include <stringify/detail/base_inline_string.hpp>
#include <stringify/access.hpp>

#define S_TO_STRING(...) ::Stringify::to_string(__VA_ARGS__)
#define S_TO_STRINGS(...) ::Stringify::to_strings(__VA_ARGS__)
#define S_TO_STRING_N(...) ::Stringify::to_string_n(__VA_ARGS__)
#define S_TO_STRINGS_N(...) ::Stringify::to_strings_n(__VA_ARGS__)

namespace Stringify {

/**
* @returns true if the type T can be converted to a string.
*/
template<class T>
constexpr bool is_convertable_to_string() {
	if (std::is_arithmetic<T>::value)
		return true;

	if (std::is_array<T>::value)
		return true;

	if (detail::__inline_to_string_defined__<T>())
		return true;

	if (Access::type_t_has_to_string_function<T>())
		return true;

	if (Access::type_t_has_operator_string<T>())
		return true;

	return std::is_pointer<T>::value;
}

namespace detail {

struct __to_string_operator__ {
	String string = "";

	template<class T>
	__to_string_operator__ &operator<<(const T &t) {
		string += to_string(t);
		return *this;
	}

	__to_string_operator__ &operator<<(const String &string) {
		this->string += string;
		return *this;
	}
};

struct __to_string_n_operator__ {
	String string = "";

	template<class T>
	__to_string_n_operator__ &operator<<(const T &t) {
		if (is_convertable_to_string<T>())
			string += to_string_n(t);
		return *this;
	}

	__to_string_n_operator__ &operator<<(const String &string) {
		this->string += string;
		return *this;
	}
};

template<class _Operator>
struct __to_string_operator_g__ {
	_Operator __op;
	String &string;

	__to_string_operator_g__(): __op(), string(__op.string) {
	}
};

template<class _Operator>
struct __to_strings_operator__ : public __to_string_operator_g__<_Operator> {
	template<class T>
	__to_strings_operator__ &operator<<(const T &t) {
		if (is_convertable_to_string<T>()) {
			this->__op << t;
			this->__op.string += ' ';
		}
		return *this;
	}
};

#if __cplusplus >= 201703L

template<class _Operator, class T, class... Args>
String __operator_string_vararg__(const T &variant, Args&&... args) {
	_Operator __op;

	__op.string = "";
	__op << variant;
	(__op << ... << args);

	return __op.string;
}

#endif

template<class T>
String __string_vararg__(const T &variant) {
	return to_string(variant);
}

template<class T, class... Args>
String __string_vararg__(const T &variant, Args&&... args) {
	return __string_vararg__(variant) + __string_vararg__(args...);
}

template<class T>
String __strings_vararg__(const T &variant) {
	return to_string(variant) + ' ';
}

template<class T, class... Args>
String __strings_vararg__(const T &variant, Args&&... args) {
	return __strings_vararg__(variant) + __strings_vararg__(args...);
}

template<class T>
String __string_n_vararg__(const T &variant) {
	return to_string_n(variant);
}

template<class T, class... Args>
String __string_n_vararg__(const T &variant, Args&&... args) {
	return __string_n_vararg__(variant) + __string_n_vararg__(args...);
}

template<class T>
String __strings_n_vararg__(const T &variant) {
	return to_string_n(variant) + ' ';
}

template<class T, class... Args>
String __strings_n_vararg__(const T &variant, Args&&... args) {
	return __strings_n_vararg__(variant) + __strings_n_vararg__(args...);
}

template<class T, class... Args>
inline String __get_vararg_string__(const T &variant, Args&&... args) {
	#if __cplusplus >= 201703L
	return __operator_string_vararg__<__to_string_operator__>(variant, args...);
	#else
	return __string_vararg__(variant, args...);
	#endif

	return "";
}

template<class T, class... Args>
inline String __get_vararg_strings__(const T &variant, Args&&... args) {
	#if __cplusplus >= 201703L
	return __operator_string_vararg__<__to_strings_operator__<__to_string_operator__>>(variant, args...);
	#else
	return __strings_vararg__(variant, args...);
	#endif

	return "";
}

template<class T, class... Args>
inline String __get_vararg_string_n__(const T &variant, Args&&... args) {
	#if __cplusplus >= 201703L
	return __operator_string_vararg__<__to_string_n_operator__>(variant, args...);
	#else
	return __string_n_vararg__(variant, args...);
	#endif

	return "";
}

template<class T, class... Args>
inline String __get_vararg_strings_n__(const T &variant, Args&&... args) {
	#if __cplusplus >= 201703L
	return __operator_string_vararg__<__to_strings_operator__<__to_string_n_operator__>>(variant, args...);
	#else
	return __strings_n_vararg__(variant, args...);
	#endif

	return "";
}


}

namespace detail {

template<class T>
constexpr __to_string_conversion_options__ __get_string_conversion_option_from_t__() {	
	if (__inline_to_string_defined__<T>())
		return __to_string_conversion_options__::__INLINE_STRING__;

	if (std::is_array<T>::value)
		return __to_string_conversion_options__::__ARRAY__;

	if (std::is_pointer<T>::value)
		return __to_string_conversion_options__::__POINTER__;

	if (std::is_arithmetic<T>::value)
		return __to_string_conversion_options__::__ARITHMETIC__;

	if (Access::type_t_has_to_string_function<T>())
		return __to_string_conversion_options__::__TO_STRING_FUNC__;

	if (Access::type_t_has_operator_string<T>())
		return __to_string_conversion_options__::__OPERATOR_STRING__;

	return __to_string_conversion_options__::__NONE__;
}

__STRINGIFY_DETAIL_DEF_CONVERSION_OPTIONS__(__to_string_conversion_options__::__ARITHMETIC__) {
	return detail::__to_string_number__(object);
}

__STRINGIFY_DETAIL_DEF_CONVERSION_OPTIONS__(__to_string_conversion_options__::__POINTER__) {
	return detail::__to_string_int_hex__(reinterpret_cast<uintptr_t>(object));
}

__STRINGIFY_DETAIL_DEF_CONVERSION_OPTIONS__(__to_string_conversion_options__::__TO_STRING_FUNC__) {
	return Access::__object_to_string__(object);
}

__STRINGIFY_DETAIL_DEF_CONVERSION_OPTIONS__(__to_string_conversion_options__::__OPERATOR_STRING__) {
	return Access::__object_string_operator__(object);
}

__STRINGIFY_DETAIL_DEF_CONVERSION_OPTIONS__(__to_string_conversion_options__::__INLINE_STRING__) {
	return detail::__inline_to_string__<T>::__to_string__(object);
}

template<class T, size_t N>
struct __inline_to_string__<T[N]> : std::true_type {
	constexpr static bool defined = true;
	inline static String __to_string__(const T variant[N]) {
		return __to_string_index_container__(variant, N);
	}
};

template<size_t N>
struct __inline_to_string__<char[N]> : std::true_type {
	constexpr static bool defined = true;
	inline static String __to_string__(const char string[N]) {
		return String(string);
	}
};

template<size_t N>
struct __inline_to_string__<const char[N]> : std::true_type {
	constexpr static bool defined = true;
	inline static String __to_string__(const char string[N]) {
		return String(string);
	}
};

}

/**
* @returns the integer converted into a hexidecimal string.
* @note the hexidecimal is big-endianess.
*/
template<class IntegerType, typename std::enable_if<std::is_integral<IntegerType>::value, bool>::type = true>
inline String to_string_hex_integer(IntegerType integer) {
	if (integer < 0)
		return detail::__to_string_int_hex__(static_cast<typename std::make_unsigned<IntegerType>::type>(integer));

	return detail::__to_string_int_hex__(integer);
}

/**
* @returns the object converted into a string.
* Users may define their own string conversion by adding an operator String or to_string function to their class.
* String conversion methods may also be included from the types directory.
* An error is generated if object cannot be converted to a string.
*/
template<class T>
inline String to_string(const T &object) {
	static_assert(is_convertable_to_string<T>(), "Cannot convert type T to a String.");

	return detail::__to_string_option__<detail::__get_string_conversion_option_from_t__<T>()>::__call__(object);
}

/**
* @returns the objects converted into a string.
* @note no spaces are added between the objects.
* Generates an error if any one of the objects cannot be converted to a string.
*/
template<class T, class... Args>
inline String to_string(const T &object, Args&&... args) {
	return detail::__get_vararg_string__(object, args...);
}

template<class T>
inline String to_strings(const T &object) {
	return to_string(object);
}

template<class T, class... Args>
inline String to_strings(const T &object, Args&&... args) {
	return detail::__get_vararg_strings__(object, args...);
}


/**
* @returns the object converted to a string, or an empty string if it cannot be converted.
* @see to_string.
*/
template<class T>
inline String to_string_n(const T &object) {
	return detail::__to_string_option__<detail::__get_string_conversion_option_from_t__<T>()>::__call__(object);
}

/**
* @returns the objects converted to a string.
* @see to_string.
* Objects which cannot be converted are ignored.
*/
template<class T, class... Args>
inline String to_string_n(const T &object, Args&&... args) {
	return detail::__get_vararg_string_n__(object, args...);
}

/**
* @brief Acts excatly like to_string_n.
*/
template<class T>
inline String to_strings_n(const T &object) {
	return detail::__to_string_option__<detail::__get_string_conversion_option_from_t__<T>()>::__call__(object);
}

template<class T, class... Args>
inline String to_strings_n(const T &object, Args&&... args) {
	return detail::__get_vararg_strings_n__(object, args...);
}

};

#endif