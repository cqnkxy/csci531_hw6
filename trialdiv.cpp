#include <iostream>
#include <fstream>
#include <vector>
#include "trialdiv.h"
#include "utility.h"
#include "bigInteger.h"

using namespace std;

bool trialdiv(
	const string &number,
	const string &primesfile,
	bool output,
	int als
){
	if (!all_dec(number)) {
		fatal("%sThe characters of %s should be [0-9]\n", string(als, ' ').c_str(), number.c_str());
	}
	bigInteger b_number(number);
	bigInteger b_end(b_number.sqrt());
	PrimesIterator itr(primesfile);
	while (true) {
		int prime = itr.next();
		if (prime < 0) {
			if (output){
				printf("%sn passes trial division test (not enough primes)\n", string(als, ' ').c_str());
			}
			return true;
		}
		bigInteger b_prime(prime);
		if (b_prime > b_end) {
			if (output) {
				printf("%sn passes trial division test\n", string(als, ' ').c_str());
			}
			return true;
		}
		if (b_number % b_prime == bigInteger(0)) {
			if (output) {
				printf("%sn is composite by trial division (mod %d = 0)\n", string(als, ' ').c_str(), prime);
			}
			return false;
		}
	}
}
