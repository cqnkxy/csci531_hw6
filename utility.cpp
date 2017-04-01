#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include "utility.h"

using namespace std;

const bool DEBUG = true;

PrimesIterator::PrimesIterator(const string &primesfile):in(primesfile.c_str()) {
	if (!in.is_open()) {
		fatal("%s can't be opened!\n", primesfile.c_str());
	}
	unsigned char byte;
	int prime = 0;
	for (int i = 0; i < 4; ++i) {
		if (!(in >> noskipws >> byte)) {
			fatal("Malformed primesfile %s\n", primesfile.c_str());
		}
		prime = (prime << 8) | byte;
	}
}

int PrimesIterator::next() {
	int prime = 0;
	unsigned char byte;
	for (int i = 0; i < 4; ++i) {
		if (!(in >> noskipws >> byte)) {
			if (i != 0) {
				fatal("Malformed primesfile\n");
			} else {
				return -1;
			}
		}
		prime = (prime << 8) | byte;
	}
	return prime;
}

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
