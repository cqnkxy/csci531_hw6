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
	PrimesIterator itr(primesfile);
	while (true) {
		int prime = itr.next();
		if (prime < 0) {
			printf("n passes trial division test (not enough primes)\n");
		}
		bigInteger b_prime(prime);
		if (b_prime > b_end) {
			printf("n passes trial division test\n");
			return;
		}
		if (b_number % b_prime == bigInteger(0)) {
			printf("n is composite by trial division (mod %d = 0)\n", prime);
			return;
		}
	}
}
