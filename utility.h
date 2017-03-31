#ifndef __UTILITY_H_
#define __UTILITY_H_

#include <iostream>
#include <string>
#include <vector>

void fatal(const char *fmt, ...);
void dprint(const char *fmt, ...);
bool all_hex(const std::string &);
bool all_dec(const std::string &);

#endif
