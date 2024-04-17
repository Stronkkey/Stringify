#ifndef __STRINGIFY_IS_DETECTED_HPP__
#define __STRINGIFY_IS_DETECTED_HPP__

#include <type_traits>

namespace Stringify {

namespace detail {

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