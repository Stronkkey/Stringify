#ifndef __STRINGIFY_PARTIAL_TO_STRING_HPP__
#define __STRINGIFY_PARTIAL_TO_STRING_HPP__

#include "string.hpp"

namespace Stringify {

template<class T>
String to_string(const T &t);

String to_string(signed char number);
String to_string(unsigned char number);
String to_string(short number);
String to_string(unsigned short number);
String to_string(int number);
String to_string(unsigned int number);
String to_string(long number);
String to_string(unsigned long number);
String to_string(long long number);
String to_string(unsigned long long number);
String to_string(float number);
String to_string(double number);
String to_string(long double number);
String to_string(bool boolean);
String to_string(char character);
String to_string(const char *string);

}

#endif