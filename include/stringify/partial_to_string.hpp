#ifndef __STRINGIFY_PARTIAL_TO_STRING_HPP__
#define __STRINGIFY_PARTIAL_TO_STRING_HPP__

#include <stringify/detail/inline_to_string.hpp>

#define __STRINGIFY_DETAIL_DEF_CONVERSION_OPTIONS__(option) \
template<> \
struct __to_string_option__<option> { \
	template<class T> \
	static String __call__(const T &object);\
}; \
template<class T> \
String __to_string_option__<option>::__call__(const T &object)

namespace Stringify {

namespace detail {

enum class __to_string_conversion_options__ {
	__NONE__,
	__ARITHMETIC__,
	__ARRAY__,
	__POINTER__,
	__TO_STRING_FUNC__,
	__OPERATOR_STRING__,
	__INLINE_STRING__,
};

template<__to_string_conversion_options__ __Option__>
struct __to_string_option__ {
	template<class T>
	static String __call__(const T&) {
		return "";
	}
};

}

template<class T>
inline String to_string(const T&);

template<class T, class... Args>
inline String to_string(const T&, Args&&...);

template<class T>
inline String to_strings(const T&);

template<class T, class... Args>
inline String to_strings(const T&, Args&&...);

template<class T>
inline String to_string_n(const T&);

template<class T, class... Args>
inline String to_string_n(const T&, Args&&...);

template<class T>
inline String to_strings_n(const T&);

template<class T, class... Args>
inline String to_strings_n(const T&, Args&&...);


}

#endif