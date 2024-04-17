#ifndef __STRINGIFY_ACCESS_HPP__
#define __STRINGIFY_ACCESS_HPP__

#include <include/function_macros.hpp>
#include <include/string.hpp>
#include <include/detail/detection.hpp>

#include <utility>

namespace Stringify {

class Access {
	template<class T>
	using __access_to_string_function__ = decltype(std::declval<const T>(). STRINGIFY_TO_STRING_NAME ());

	template<class T>
	using __access_operator_string__ = decltype(String(std::declval<const T>()));

	template<class T>
	static constexpr bool __t_has_to_string__() {
		return detail::detection::is_detected<__access_to_string_function__, T>::value;
	}

	template<class T>
	static constexpr bool __t_has_operator_string__() {
		return detail::detection::is_detected<__access_operator_string__, T>::value;
	}
public:
	Access() = delete;
	~Access() = delete;

	template<class T>
	static constexpr bool type_t_has_to_string_function() {
		return __t_has_to_string__<T>();
	}

	template<class T>
	static constexpr bool type_t_has_operator_string() {
		return __t_has_operator_string__<T>();
	}

	template<class T>
	static inline String __object_to_string__(const T &object) {
		return object.STRINGIFY_TO_STRING_NAME();
	}

	template<class T>
	static inline String __object_string_operator__(const T &object) {
		return String(object);
	}
};

}

#endif