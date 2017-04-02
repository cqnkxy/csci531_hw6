#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "maurer.h"
#include "bigInteger.h"
#include "utility.h"
#include "rndsearch.h"
#include "trialdiv.h"
#include "millerrabin.h"

using namespace::std;

// Maurer(k):
//     1) if (k <= 20) do forever {
//        1.1) n = RndOddNum(k)
//        1.2) if (TrialDivision(n) == "pass") return n
//        }
//     2) c = 0.1, m = 20
//     3) B = c * k^2 (not used)
//     4) (generate a fraction r, the size of q relative to n)
//        4.1) if (k <= 2m) r = 0.5
//        4.2) if (k > 2m) do forever {
//             4.2.1) r = RndByte() / 255.0
//             4.2.2) r = 0.5 + r / 2.0
//             4.2.3) if (k*(1-r) > m) break;
//             }
//     5) (recursion) q = Maurer(floor(r*k)+1)
//     6) num_bits_in_q = BN_num_bits(q)
//        I = floor(2^(k-2) / q)
//     7) do forever {
//        7.1) R = RndOddNum(k+1-num_bits_in_q)
//             R = (R mod I) + I + 1
//             n = 2Rq+1
//        7.2) if (TrialDivision(n) != "fail") {
//                    num_bits_in_n = BN_num_bits(n)
//             7.2.1) do {
//                        a = RndOddNum(num_bits_in_n)
//                    } while (a <= 1 or a >= n-1))
//             7.2.2) b = a^{n-1} mod n
//                    if (b == 1) {
//                        b = a^{2R} mod n
//                        d = gcd(b-1,n)
//                        if (d == 1) return(n)
//                    }
//             }
//        }
bigInteger maurer(int lvl, int k, istream &in, const string &primesfile) {
	printf("Maurer: level %d, k=%d\n", lvl, k);
	bigInteger n;
	if (k <= 20){
		while(true) {
			n = RndOddNum(k, in);
			printf("  step 1.1, n = %s\n", n.getNumber().c_str());
			if (trialdiv(n.getNumber(), primesfile, true, 4)) {
				return n;
			}
		}
	}
	double r = 0;
	int m = 20;
	if (k <= 2*m) {
		r = 0.5;
		printf("  step 4, r = 50%%\n");
	} else {
		unsigned char byte;
		while (true){
			in >> byte;
			r = byte / 255.0;
			r = 0.5 + r / 2.0;
			if (k * (1-r) > m) {
				break;
			}
		}
		printf("  step 4: random byte = %d, r = %2.0f%%\n", int(byte), r*100);
	}
	bigInteger q = maurer(lvl+1, floor(r*k)+1, in, primesfile);
	printf("Maurer: back to level %d, k=%d, q=%s\n", 
		lvl, k, q.getNumber().c_str());
	size_t num_bits_in_q = q.bits();
	bigInteger I = bigInteger(2).power(k-2) / q;
	for (size_t i = 1; ; ++i) {
		bigInteger R = RndOddNum(k+1-num_bits_in_q, in);
		R = (R % I) + I + 1;
		n = R * q * 2 + 1;
		printf("  step 7, itr %zd: R = %s, n = %s\n",
			i, R.getNumber().c_str(), n.getNumber().c_str());
		if (trialdiv(n.getNumber(), primesfile, true, 4)) {
			bigInteger a;
			do {
				a = RndOddNum(n.bits(), in);
			} while (a <= 1 || a >= n-1);
			printf("  step 7.2.1, itr %zd: a = %s\n", i, a.getNumber().c_str());
			bigInteger b = computeY(a, n-1, n);
			if (b == 1) {
				b = computeY(a, R*2, n);
				bigInteger d = gcd(b-1, n);
				if (d == 1) {
					return n;
				}
			}
		}
	}
}

void maurer(
	const string &numbits,
	const string &primesfile,
	const string &rndfile
){
	if (!all_dec(numbits)) {
		fatal("%s must be all [0-9]\n", numbits.c_str());
	}
	ifstream in(rndfile.c_str());
	if (!in.is_open()) {
		fatal("Can't open file %s\n", primesfile.c_str());
	}
	int k = atoi(numbits.c_str());
	bigInteger n = maurer(0, k, in, primesfile);
	printf("\nMaurer's Algorithm found an %zd-bit prime:\n  n = %s\n", 
		n.bits(), n.getNumber().c_str());
}
