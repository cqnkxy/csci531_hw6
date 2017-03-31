#include <iostream>
#include <vector>
#include <cmath>
#include <arpa/inet.h>
#include "utility.h"
#include "primes.h"

using namespace::std;

// Sieve of Eratosthenes. Use one bit for a number.
void primes(int maxval) {
	size_t sz = ceil((double)maxval/8);
	vector<unsigned char> candicates(sz+1, 0xff);
	for (int num = 2; num*num <= maxval; ++num) {
		bool isPrime = candicates[num/8] & (1 << (num%8));
		if (isPrime) {
			for (int composite = num*num; composite <= maxval; composite += num) {
				candicates[composite/8] &= ~(1 << composite%8);
			}
		}
	}
	int big_endian = htonl(maxval);
	fwrite(&big_endian, sizeof(int), 1, stdout);
	for (int num = 2; num <= maxval; ++num) {
		bool isPrime = candicates[num/8] & (1 << (num%8));
		if (isPrime) {
			int big_endian = htonl(num);
			fwrite(&big_endian, sizeof(int), 1, stdout);
		}
	}
}
