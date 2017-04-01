#include <iostream>
#include <fstream>
#include <vector>
#include "trialdiv.h"
#include "utility.h"
#include "bigInteger.h"

using namespace std;

void trialdiv(const string &number, const string &primesfile) {
	if (!all_dec(number)) {
		fatal("The characters of %s should be [0-9]\n", number.c_str());
	}
	bigInteger b_number(number);
	bigInteger b_end(b_number.sqrt());
	ifstream in(primesfile);
	if (!in.is_open()) {
		fatal("%s can't be opened!\n", primesfile.c_str());
	}
	unsigned char byte;
	int maxVal = -1, prime = -2;
	while (true) {
		prime = 0;
		for (int i = 0; i < 4; ++i) {
			if (!(in >> noskipws >> byte)) {
				fatal("Malformed primesfile %s\n", primesfile.c_str());
			}
			prime = (prime << 8) | byte;
		}
		if (maxVal < 0) {
			maxVal = prime;
			continue;
		}
		bigInteger b_prime(prime);
		if (b_prime > b_end) {
			printf("%s passes trial division test\n", number.c_str());
			return;
		}
		if (b_number % b_prime == bigInteger(0)) {
			printf("%s is composite by trial division (mod %d = 0)\n",
				number.c_str(), prime);
			return;
		}
		if (maxVal == prime) {
			break;
		}
	}
	printf("%s passes trial division test (not enough primes)\n", number.c_str());
}
