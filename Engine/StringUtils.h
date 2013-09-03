#ifndef _TRANQUILITYSTRING_UTILS_H_
#define _TRANQUILITYSTRING_UTILS_H_

#include "common.h"

std::vector<std::string> split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

// trim from the left
std::string &ltrim(std::string &s);

// trim from the right
std::string &rtrim(std::string &s);

// trim from both ends
std::string &trim(std::string &s);

#endif