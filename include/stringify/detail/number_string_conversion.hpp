/** @file number_string_conversion.hpp
    @brief String conversion methods for number types. */
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
#ifndef __STRINGIFY_NUMBER_STRING_CONVERSION_HPP__
#define __STRINGIFY_NUMBER_STRING_CONVERSION_HPP__

#include <stringify/string.hpp>

#include <cmath>
#include <cstdint>
#include <type_traits>

namespace Stringify {

namespace detail {

/**
* @brief equivalent to pow(10, exponent).
*/
constexpr size_t __pow_10__(size_t exponent) {
	size_t pow_of_10 = 10;

	for (size_t i = 1; i < exponent; i++)
		pow_of_10 *= 10;

	return pow_of_10;
}

/**
* @brief copies source into destination.
*/
constexpr void __str_copy__(const char *source, char *destination) {
	for (size_t i = 0; source[i] != '\0'; i++)
		destination[i] = source[i];
}

/**
* @brief Writes an integral number into a string.
* @param length the length of the string. Can be smaller than the string length but not bigger.
* The behavior is undefined if the string length is smaller than the length given.
*/
template<class T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
constexpr void __to_10_characters__(char *string, unsigned int length, T number) noexcept {
	constexpr const char precomputed_digits[201] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
	unsigned i = length - 1;

	while (number >= 100) {
		auto const num = (number % 100) * 2;
		number /= 100;
		string[i] = precomputed_digits[num + 1];
		string[i - 1] = precomputed_digits[num];
		i -= 2;
	}
	
	if (number >= 10) {
	  auto const num = number * 2;
	  string[1] = precomputed_digits[num + 1];
	  string[0] = precomputed_digits[num];
	} else
		string[0] = '0' + number;
}

/**
* @brief Writes the integral part of a floating point number into a string.
* @param length the length of the string. Can be smaller than the string length but not bigger.
* The behavior is undefined if the string length is smaller than the length given.
*/
template<class T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
inline void __to_10_characters__(char *string, unsigned int length, T number) noexcept {
	constexpr const char digits[201] = "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899";
	unsigned i = length - 1;

	while (number >= 100) {
		size_t num = std::fmod(number, 100) * 2;
		number = std::trunc(number / 100);
		string[i] = digits[num + 1];
		string[i - 1] = digits[num];
		i -= 2;
	}
	
	if (number >= 10) {
	  size_t num = number * 2;
	  string[1] = digits[num + 1];
	  string[0] = digits[num];
	} else
		string[0] = '0' + number;
}

/**
* @returns the minimum amount of characters required to store a number in a string.
* @param base the base numeral system (e.g. 16 for hex).
* @note +1 is added to the return value if the number is negative, to account for the '-' sign.
*/
template<class NumberType, typename std::enable_if<std::is_integral<NumberType>::value, bool>::type = true>
constexpr size_t __get_string_length_from_number__(NumberType number, NumberType base = 10) {
	size_t i = 1;

	if (number < 0) {
		i += 1;
		number = -number;
	}

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

/**
* @returns the amount of characters required to store the number in a string.
*/
template<class FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, bool>::type = true>
constexpr size_t __get_string_length_from_number__(FloatType number, FloatType base = 10, size_t decimal_places = 6) {
	using __numeric_limits__ = std::numeric_limits<FloatType>;

	if (number > __numeric_limits__::max() || number != number)
		return 3; // NAN

	if (number < __numeric_limits__::lowest())
		return 4; // -NAN

	size_t i = 1;
	const size_t fixed_size = decimal_places + 1;

	if (number < 0) {
		i += 1;
		number = -number;
	}

	const FloatType base2 = base  * base;
	const FloatType base3 = base2 * base;
	const FloatType base4 = base3 * base;

	while (true) {
		if (number < base)
			return i + fixed_size;
		if (number < base2)
			return i + 1 + fixed_size;
		if (number < base3)
			return i + 2 + fixed_size;
		if (number < base4)
			return i + 3 + fixed_size;
		number /= base4;
		i += 4;
	}
}

/**
* @brief writes an integer number into a string.
* @param length the maximum amount of characters that should be written into the string.
* The behavior is undefined if the string length is smaller than the length given.
*/
template<class T, typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value, bool>::type = true>
constexpr void __number_into_string__(T number, char *string, size_t length) {
	const bool is_negative = number < 0;
	string[0] = '-';
	detail::__to_10_characters__(&string[is_negative], length, is_negative ? -number : number);
}

/**
* @brief writes an integer number into a string.
* @param length the maximum amount of characters that should be written into the string.
* The behavior is undefined if the string length is smaller than the length given.
*/
template<class T, typename std::enable_if<std::is_integral<T>::value && std::is_unsigned<T>::value, bool>::type = true>
constexpr void __number_into_string__(T number, char *string, size_t length) {
	detail::__to_10_characters__(string, length, number);
}

/**
* @brief writes a floating point number into a string.
* @param decimal_places the amount of decimal numbers in the string.
*/
template<class FloatType, typename std::enable_if<std::is_floating_point<FloatType>::value, bool>::type = true>
inline void __number_into_string__(FloatType number, char *string, size_t decimal_places = 6) {
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
		__str_copy__("nan", string);
		return;
	}

	const bool is_negative = number < 0;
	FloatType integral_part = is_negative ? std::trunc(-number) : std::trunc(number);
	const FloatType decimals = (is_negative ? -number : number) - integral_part;
	size_t integral_length = __get_string_length_from_number__(integral_part, 10.0, 0) - 1;
	size_t pos = 0;

	if (is_negative)
		string[pos++] = '-';

	__to_10_characters__(&string[pos], integral_length, integral_part);

	pos += integral_length;
	string[pos++] = '.';

	const FloatType integral_decimals = decimals * __pow_10__(decimal_places);
	const size_t integral_decimals_length = __get_string_length_from_number__(integral_decimals, 10.0, 0) - 1;
	__to_10_characters__(&string[pos], integral_decimals_length, integral_decimals);

	pos += integral_decimals_length;
	if (integral_decimals_length < decimal_places)
		for (size_t i = integral_decimals_length; i < decimal_places; i++)
			string[pos++] = '0';
}

/**
* @returns the number converted to a string.
*/
template<class T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
inline String __to_string_number__(T number) {
	String number_string;
	number_string.resize(__get_string_length_from_number__(number));

	__number_into_string__(number, &number_string[0], __get_string_length_from_number__(number));
	return number_string;
}

/**
* @returns the number converted to a string.
*/
template<class T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
inline String __to_string_number__(T number) {
	String number_string;
	number_string.resize(__get_string_length_from_number__(number));

	__number_into_string__(number, &number_string[0]);
	return number_string;
}

template<class NumberType, typename std::enable_if<std::is_arithmetic<NumberType>::value, bool>::type = true>
constexpr size_t __get_hex_int_string_size__(NumberType number) {
	return __get_string_length_from_number__(number, static_cast<NumberType>(16));
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

}

}

#endif