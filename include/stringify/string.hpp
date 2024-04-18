#ifndef __STRINGIFY_STRING_HPP__
#define __STRINGIFY_STRING_HPP__

#ifndef STRINGIFY_STRING_TYPE
#include <string>
#define STRINGIFY_STRING_TYPE ::std::string
#endif


#ifndef STRINGIFY_STRING_VIEW_TYPE
#if __cplusplus >= 201703L
#include <string_view>
#define STRINGIFY_STRING_VIEW_TYPE ::std::basic_string_view<STRINGIFY_STRING_TYPE::value_type>
#else
#define STRINGIFY_STRING_VIEW_TYPE STRINGIFY_STRING_TYPE
#endif
#endif

namespace Stringify {

using String = STRINGIFY_STRING_TYPE;
using StringView = STRINGIFY_STRING_VIEW_TYPE;

}

#endif