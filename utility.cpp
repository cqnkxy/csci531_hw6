#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "utility.h"

using namespace std;

const bool DEBUG = true;

void fatal(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

void dprint(const char *fmt, ...) {
	if (DEBUG) {
		va_list args;
		va_start(args, fmt);
		vprintf(fmt, args);
		va_end(args);
	}
}

bool all_hex(const string &str) {
	for (size_t i = 0; i < str.size(); ++i) {
		char ch = tolower(str[i]);
		if (!(('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'f'))) {
			return false;
		}
	}
	return true;
}

bool all_dec(const string &str) {
	for (size_t i = 0; i < str.size(); ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}
