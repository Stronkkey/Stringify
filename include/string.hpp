#ifndef __STRINGIFY_STRING_HPP__
#define __STRINGIFY_STRING_HPP__

#ifndef STRINGIFY_STRING_TYPE
#include <string>
#define STRINGIFY_STRING_TYPE std::string
#endif

namespace Stringify {

using String = STRINGIFY_STRING_TYPE;

}

#endif