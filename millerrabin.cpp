#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cassert>
#include "millerrabin.h"
#include "bigInteger.h"
#include "utility.h"

using namespace std;

// Miller-Rabin(n,maxitr):
//     1) write n-1 = (2^s)r such that r is odd
//     2) for (i=1; i <= maxitr; i++) {
//        2.1) a = the ith smallest prime number
//             2.1.1) if (a ≥ n-1) return("failure")
//        2.2) compute y = a^r mod n
//        2.3) if (y != 1 and y != n-1) {
//             2.3.1) for (j=1; j <= s-1 and y != n-1; j++) {
//                    2.3.1.1) y = y2 mod n
//                    2.3.1.2) if (y == 1) return("composite")
//                    }
//             2.3.2) if (y != n-1) return("composite")
//             }
//        }
//     3) return("prime")

bigInteger computeY(const bigInteger &a, const bigInteger &r, const bigInteger &n) {
	if (r == 1) {
		return a % n;
	}
	if (r == 0) {
		return 1;
	}
	pair<bigInteger, bigInteger> res = divmod(r, 2);
	bigInteger half = computeY(a, res.first, n);
	if (res.second == 1) {
		return half * half * a % n;
	}
	return half * half % n;
}

bool millerrabin(
	const string &number,
	const string &maxitr,
	const string &primefile,
	bool output,
	int als
){
	if (!all_dec(number) || !all_dec(maxitr)) {
		fatal("%s and %s must be all [0-9]\n", number.c_str(), maxitr.c_str());
	}
	PrimesIterator itr(primefile);
	bigInteger n(number), r, tmp = n-1;
	int s = 0;
	while (true) {
		pair<bigInteger, bigInteger> res = divmod(tmp, 2);
		if (res.second != 0) {
			r = tmp;
			break;
		}
		s += 1;
		tmp = res.first;
	}
	if (output) {
		if (als == 0) {
			printf("n = %s\n", number.c_str());
		}
		printf("  %sn-1 = %s\n", string(als, ' ').c_str(), (n-1).getNumber().c_str());
		printf("  %ss = %d\n", string(als, ' ').c_str(), s);
		printf("  %sr = %s\n", string(als, ' ').c_str(), r.getNumber().c_str());
	}
	int n_maxitr = atoi(maxitr.c_str());
	assert(r % 2 == 1);
	for (int i = 1; i <= n_maxitr; ++i ){
		int prime = itr.next();
		assert(prime > 0);
		bigInteger a(prime);
		if (a >= n-1) {
			if (output) {
				printf("  %sItr %d of %d, a = %s (failed)\n", 
					string(als, ' ').c_str(), i, n_maxitr, a.getNumber().c_str());
				printf("%sMiller-Rabin failure, maxitr is too large\n", string(als, ' ').c_str());
			}
			return false;
		}
		bigInteger y = computeY(a, r, n);
		if (output){
			printf("  %sItr %d of %d, a = %s, y = %s",
				string(als, ' ').c_str(), i, n_maxitr, a.getNumber().c_str(), y.getNumber().c_str());
			if (y == n-1) {
				printf(" (which is n-1)\n");
			} else {
				printf("\n");
			}
		}
		if (y != 1 && y != n-1) {
			for (int j = 1; j <= s-1 && y != n-1; ++j) {
				y = y*y%n;
				if (output) {
					printf("    %sj = %d of %d, y = %s", string(als, ' ').c_str(), j, s-1, y.getNumber().c_str());
					if (y == n-1) {
						printf(" (which is n-1)\n");
					} else {
						printf("\n");
					}
				}
				if (y == 1) {
					if (output) {
						printf("%sMiller-Rabin found a strong witness %d\n", string(als, ' ').c_str(), prime);
					}
					return false;
				}
			}
			if (y != n-1) {
				if (output){
					printf("%sMiller-Rabin found a strong witness %d\n", string(als, ' ').c_str(), prime);
				}
				return false;
			}
		}
	}
	if (output) {
		printf("%sMiller-Rabin declares n to be a prime number\n", string(als, ' ').c_str());
	}
	return true;
}
