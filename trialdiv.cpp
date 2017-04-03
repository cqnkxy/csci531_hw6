#include <iostream>
#include <fstream>
#include <vector>
#include <openssl/bn.h>
#include <cassert>
#include <arpa/inet.h>
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
	bigInteger sqrt = bigInteger(number).sqrt();
	BIGNUM *b_number = BN_new();
	BIGNUM *b_end = BN_new();
	BIGNUM *b_prime = BN_new();
	BIGNUM *b_rem = BN_new();
	BN_CTX *ctx = BN_CTX_new();
	assert(b_number != NULL && b_end != NULL && b_prime != NULL && b_rem != NULL);
	BN_dec2bn(&b_number, number.c_str());
	BN_dec2bn(&b_end, sqrt.getNumber().c_str());
	PrimesIterator itr(primesfile);
	bool ret = false;
	while (true) {
		int prime = itr.next();
		if (prime < 0) {
			if (output){
				printf("%sn passes trial division test (not enough primes)\n", string(als, ' ').c_str());
			}
			ret = true;
			break;
		}
		prime = htonl(prime);
		BN_bin2bn((unsigned char *)&prime, sizeof(uint32_t), b_prime);

		if (BN_cmp(b_prime, b_end) > 0) {
			if (output) {
				printf("%sn passes trial division test\n", string(als, ' ').c_str());
			}
			ret = true;
			break;
		}
		BN_mod(b_rem, b_number, b_prime, ctx);
		if (BN_is_zero(b_rem)) {
			if (output) {
				printf("%sn is composite by trial division (mod %d = 0)\n", string(als, ' ').c_str(), prime);
			}
			ret = false;
			break;
		}
	}
	BN_free(b_number);
	BN_free(b_end);
	BN_free(b_prime);
	BN_free(b_rem);
	BN_CTX_free(ctx);
	return ret;
}
