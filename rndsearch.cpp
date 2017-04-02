#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include "utility.h"
#include "trialdiv.h"
#include "millerrabin.h"

using namespace::std;

// Random-Search(k,maxitr):
//     1) n = RndOddNum(k)
//     2) if (TrialDivision(n) == "fail") goto step (1)
//     3) if (Miller-Rabin(n,maxitr) == "prime") return(n)
//        goto step (1)
// Let x = ceil(k/8). RndOddNum(k) first reads x bytes from rndfile and
// converts the data into a BIGNUM representation using BN_bin2bn()
// (first byte read is the most significant byte in BIGNUM). RndOddNum(k)
// then sets both bit zero (the least significant bit) and bit k-1 to one, 
// sets all bits from k and above to zero in the BIGNUM, and returns the 
// resulting BIGNUM.

bigInteger RndOddNum(int k, istream &in) {
	int x = ceil((double)k/8);
	unsigned char byte;
	string bytes;
	for (int j = 0; j < x; ++j) {
		if (!(in >> noskipws >> byte)) {
			fatal("Not enough data in the rndfile!\n");
		}
		bytes += byte;
	}
	reverse(bytes.begin(), bytes.end());
	// set 0 bit and k-1 bit to 1
	bytes[0] |= 0x01;
	bytes[(k-1)/8] |= 0x01 << ((k-1) % 8);
	// set k bit and above to 0
	unsigned char mask = 0xff;
	for (int i = k % 8; i < 8; ++i) {
		mask &= ~(1 << i);
	}
	bytes[k/8] &= mask;
	reverse(bytes.begin(), bytes.end());
	return binToBigInteger(bytes);
}

void rndsearch(
	const std::string &numbits,
	const std::string &maxitr,
	const std::string &primesfile,
	const std::string &rndfile
){
	ifstream in(rndfile.c_str());
	if (!in.is_open()) {
		fatal("File %s can't be opened\n", rndfile.c_str());
	}
	if (!all_dec(maxitr) || !all_dec(numbits)) {
		fatal("maxitr and numbits must be [0-9]\n");
	}
	int k = atoi(numbits.c_str());
	for (int i = 1; ; ++i) {
		printf("RANDOM-SEARCH: iteration %d\n", i);
		bigInteger n = RndOddNum(k, in);
		printf("  n = %s\n", n.getNumber().c_str());
		if (!trialdiv(n.getNumber(), primesfile, true, 2)) {
			continue;
		}
		if (millerrabin(n.getNumber(), maxitr, primesfile, true, 2)) {
			break;
		}
	}
}
