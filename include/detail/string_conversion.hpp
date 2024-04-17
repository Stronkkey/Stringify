#ifndef __STRINGIFY_STRING_CONVERSION_HPP__
#define __STRINGIFY_STRING_CONVERSION_HPP__

#include <include/access.hpp>
#include <include/detail/inline_to_string.hpp>
#include <include/partial_to_string.hpp>

#include <cmath>
#include <cstdint>
#include <limits>

namespace Stringify {

namespace detail {

template<class T>
constexpr void __to_10_characters__(char *first, unsigned int length, T number) noexcept {
	constexpr const char digits[201] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
	unsigned i = length - 1;

	while (number >= 100) {
		auto const num = (number % 100) * 2;
		number /= 100;
		first[i] = digits[num + 1];
		first[i - 1] = digits[num];
		i -= 2;
	}
	
	if (number >= 10) {
	  auto const num = number * 2;
	  first[1] = digits[num + 1];
	  first[0] = digits[num];
	} else
		first[0] = '0' + number;
}

template<class T>
inline void __to_10_charactersf__(char *first, unsigned int length, T number) noexcept {
	constexpr const char digits[201] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
	unsigned i = length - 1;

	while (number >= 100) {
		size_t num = std::fmod(number, 100) * 2;
		number = std::trunc(number / 100);
		first[i] = digits[num + 1];
		first[i - 1] = digits[num];
		i -= 2;
	}
	
	if (number >= 10) {
	  size_t num = number * 2;
	  first[1] = digits[num + 1];
	  first[0] = digits[num];
	} else
		first[0] = '0' + number;
}

template<class NumberType>
constexpr size_t __log__(NumberType number, NumberType base = 10) {
	static_assert(std::is_arithmetic<NumberType>::value, "T must be a number type.");

	size_t i = 1;
	const NumberType base2 = base  * base;
	const NumberType base3 = base2 * base;
	const NumberType base4 = base3 * base;

	while (true) {
		if (number < base)
			return i;
		if (number < base2)
			return i + 1;
		if (number < base3)
			return i + 2;
		if (number < base4)
			return i + 3;
		number /= base4;
		i += 4;
	}
}

template<class T>
constexpr size_t __get_string_length_from_number__(T number) {
	if (number < 0)
		return __log__(-number) + 1;
	return __log__(number);
}

template<class T>
constexpr void __signed_number_into_string__(T number, char *string, size_t length) {
	static_assert(std::is_integral<T>::value, "T must be an number type.");
	static_assert(std::is_signed<T>::value, "T must be a signed number type.");

	const bool is_negative = number < 0;

	if (is_negative)
		string[0] = '-';
	
	detail::__to_10_characters__(&string[is_negative], length, is_negative ? -number : number);
}

template<class T>
inline void __unsigned_number_into_string__(T number, char *string, size_t length) {
	static_assert(std::is_integral<T>::value, "T must be an number type.");
	static_assert(std::is_unsigned<T>::value, "T must be a unsigned number type.");

	detail::__to_10_characters__(string, length, number);
}

template<class T>
inline String __to_string_signed_number__(T number) {
	static_assert(std::is_integral<T>::value, "T must be an number type.");
	static_assert(std::is_signed<T>::value, "T must be a signed number type.");

	String number_string;
	number_string.resize(__get_string_length_from_number__(number));

	__signed_number_into_string__(number, &number_string[0], __get_string_length_from_number__(number));
	return number_string;
}

template<class T>
inline String __to_string_unsigned_number__(T number) {
	static_assert(std::is_integral<T>::value, "T must be an number type.");
	static_assert(std::is_unsigned<T>::value, "T must be a unsigned number type.");

	String number_string;
	number_string.resize(__get_string_length_from_number__(number));

	__unsigned_number_into_string__(number, &number_string[0], __get_string_length_from_number__(number));
	return number_string;
}

constexpr size_t __pow_10__(size_t exponent) {
	size_t pow_of_10 = 10;

	for (size_t i = 1; i < exponent; i++)
		pow_of_10 *= 10;

	return pow_of_10;
}

template<class FloatType>
constexpr size_t __get_string_length_from_float__(FloatType number, size_t decimal_places = 6) {
	using __numeric_limits__ = std::numeric_limits<FloatType>;

	if (number > __numeric_limits__::max() || number != number)
		return 3;

	if (number < __numeric_limits__::lowest())
		return 4;

	FloatType integral_part = number < 0 ? -number : number;

	return __get_string_length_from_number__(integral_part) + (number < 0) + decimal_places + 1;
}

constexpr void __str_copy__(const char *source, char *destination) {
	for (size_t i = 0; source[i] != '\0'; i++)
		destination[i] = source[i];
}

template<class FloatType>
inline void __float_number_into_string__(FloatType number, char *string, size_t decimal_places = 6) {
	using __numeric_limits__ = std::numeric_limits<FloatType>;

	if (number > __numeric_limits__::max()) {
		__str_copy__("inf", string);
		return;
	}

	if (number < __numeric_limits__::lowest()) {
		__str_copy__("-inf", string);
		return;
	}

	if (number != number) {
		__str_copy__("nan", &string[0]);
		return;
	}

	const bool is_negative = number < 0;
	FloatType integral_part = is_negative ? std::trunc(-number) : std::trunc(number);
	const FloatType decimals = (is_negative ? -number : number) - integral_part;
	size_t integral_length = __get_string_length_from_number__(integral_part);
	size_t pos = 0;

	if (is_negative)
		string[pos++] = '-';

	__to_10_charactersf__(&string[pos], integral_length, integral_part);

	pos += integral_length;
	string[pos++] = '.';

	const FloatType integral_decimals = decimals * __pow_10__(decimal_places);
	const size_t integral_decimals_length = __get_string_length_from_number__(integral_decimals);
	__to_10_charactersf__(&string[pos], integral_decimals_length, integral_decimals);

	pos += integral_decimals_length;
	if (integral_decimals_length < decimal_places)
		for (size_t i = integral_decimals_length; i < decimal_places; i++)
			string[pos++] = '0';
}

template<class FloatType>
inline String __to_string_float_number__(FloatType number) {
	static_assert(std::is_floating_point<FloatType>::value, "FloatType must be a floating pointer number type.");

	String string;
	string.resize(__get_string_length_from_float__(number));

	__float_number_into_string__(number, &string[0]);
	return string;
}

template<class NumberType>
inline size_t __get_hex_int_string_size__(NumberType number) {
	return __log__(static_cast<uint_fast64_t>(number), static_cast<uint_fast64_t>(16));
}

template<class IntegerType>
inline String __to_string_int_hex__(IntegerType integer) {
	const char hex_digits[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	const size_t string_size = 2 + __get_hex_int_string_size__(integer);
	
	String string;
	size_t string_index = string_size - 1;

	int_fast64_t quotient = 1;
	IntegerType start_number = integer;

	string.resize(string_size);
	string[0] = '0';
	string[1] = 'x';

	while (quotient > 0) {
		quotient = (start_number / 16);
		string[string_index] = hex_digits[(start_number % 16)];
		start_number = quotient;
		string_index--;
	}

	for (size_t i = 2; i <= string_index; i++)
		string[i] = '0';

	return string;
}

template<bool>
struct __explicitly_convertible_to_string__;

template<>
struct __explicitly_convertible_to_string__<false> {
	template<class T>
	static String __convert_to_string__(const T&) {
		return "{}";
	}
};

template<>
struct __explicitly_convertible_to_string__<true> {
	template<class T>
	static String __convert_to_string__(const T &object) {
		return Access::__object_string_operator__(object);
	}
};

template<class T, bool = std::is_array<T>::value>
struct __string_array__;

template<class T>
struct __remove_array_qf__;

template<class T>
struct __remove_array_qf__ {
	using value_type = T;
};

template<class T>
struct __remove_array_qf__<T[]> {
	using value_type = T;
};

template<class T, size_t N>
struct __remove_array_qf__<T[N]> {
	using value_type = T;
};

template<class T, size_t N>
struct __remove_array_qf__<T[][N]> {
	using value_type = typename __remove_array_qf__<T>::value_type;
};

template<class T, size_t N, size_t N2>
struct __remove_array_qf__<T[N][N2]> {
	using value_type = typename __remove_array_qf__<T>::value_type;
};

template<class T>
using __to_string_func__ = decltype(std::declval<const T>().to_string());

template<class T>
using __has_to_string__ = detection::detected_or<void, __to_string_func__, T>;

template<class T>
constexpr bool __has_to_string_function__() {
	return std::is_same<typename __has_to_string__<T>::type, Stringify::String>::value;
}

template<class T>
constexpr bool __can_t_be_converted_to_string__() {
	if (std::is_convertible<T, String>::value)
		return true;

	if (std::is_array<T>::value)
		return true;

	if (__is_inline_to_string_defined__<T>())
		return true;

	if (Access::type_t_has_to_string_function<T>())
		return true;

	if (Access::type_t_has_operator_string<T>())
		return true;

	return std::is_pointer<T>::value;
}

template<class T>
struct __string_array__<T, false> {
	static Stringify::String __get_string__(const T &variant) {
		return to_string(variant);
	}
};

template<class T>
struct __string_array__<T[1], true> {
	static Stringify::String __get_string__(const T variant[1]) {
		return to_string(*variant);
	}
};

template<class T>
struct __string_array__<T, true> {
	static Stringify::String __get_string__(const T &array) {
		size_t element_count = sizeof(T) / sizeof(decltype(array[0]));
		Stringify::String str = "{";

		for (size_t i = 0; i < element_count; i++)
			str += __string_array__<decltype(array[0])>::__get_string__(array[i]) + ", ";

		str.resize(str.size() - 1);
		str[str.size() - 1] = '}';

		return str;
	}
};

template<class Container>
inline String __to_string_generic_iterator_container__(const Container &container) {
	String string = "{";

	for (const auto &element: container)
		string += to_string(element) + ", ";

	string.resize(string.size() - 1);
	string[string.size() - 1] = '}';

	return string;
}

template<class Container>
inline String __to_string_generic_index_container__(const Container &container, size_t container_size) {
	String string = "{";

	for (size_t i = 0; i < container_size; i++) {
		if ((i + 1) == container_size)
			string += to_string(container[i]);
		else
			string += to_string(container[i]) + ", ";
	}

	string += '}';

	return string;
}

struct __to_string_operator__ {
	String string = "";

	template<class T>
	void operator<<(const T &t) {
		string += to_string(t);
	}

	void operator<<(const String &string) {
		this->string += string;
	}
};

struct __to_strings_operator__ {
	__to_string_operator__ __op;

	template<class T>
	void operator<<(const T &t) {
		__op << t;
		__op.string += ' ';
	}
};
	
#if __cplusplus >= 201703L

template<class _Operator, class T, class... Args>
String __operator_string_vararg__(const T &variant, const Args&... args) {
	_Operator __op;

	__op.string = "";
	__op << variant;
	(__op << ... << args);

	return __op.string;
}

#else

template<class T>
String __string_vararg__(const T &variant) {
	return to_string(variant);
}

template<class T, class... Args>
String __string_vararg__(const T &variant, const Args&... args) {
	return __string_vararg__(variant) + __string_vararg__(args...);
}

template<class T>
String __strings_vararg__(const T &variant) {
	return to_string(variant) + ' ';
}

template<class T, class... Args>
String __strings_vararg__(const T &variant, const Args&... args) {
	return __strings_vararg__(variant) + __strings_vararg__(args...);
}

#endif

template<class T, class... Args>
inline String __get_vararg_string__(const T &variant, const Args&... args) {
	#if __cplusplus >= 201703L

	return __operator_string_vararg__<__to_string_operator__>(variant, args...);

	#else

	return __string_vararg__(variant, args...);

	#endif

	return "";
}

template<class T, class... Args>
inline String __get_vararg_strings__(const T &variant, const Args&... args) {
	#if __cplusplus >= 201703L

	return __operator_string_vararg__<__to_strings_operator__>(variant, args...);

	#else

	return __strings_vararg__(variant, args...);

	#endif

	return "";
}

inline String __quote_string__(const String &string) {
	size_t string_size = string.size() + 2;
	String string_copy;
	string_copy.resize(string_size);

	string_copy[0] = '\"';
	string_copy[string_size - 1] = '\"';
	string.copy(&string_copy[1], string.size());

	return string_copy;
}

inline void __quote_string__(String &string) {
	size_t string_size = string.size() + 2;
	String string_copy = std::move(string);

	string.resize(string_size);
	string[0] = '\"';
	string[string_size] = '\"';
	string.copy(&string_copy[1], string_copy.size());
}

template<class Container>
inline String __to_string_generic_iterator_pair_container__(const Container &container) {
	String string = "{";

	for (const auto &iterator: container)
		string += __quote_string__(to_string(iterator.first)) + ": " + __quote_string__(to_string(iterator.second)) + ", ";

	string.resize(string.size() - 1);
	string[string.size() - 1] = '}';

	return string;
}

}

}

#endif