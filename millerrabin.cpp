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

bigInteger computeY(bigInteger &a, bigInteger &r, bigInteger &n) {
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

void millerrabin(
	const string &number,
	const string &maxitr,
	const string &primefile
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
	printf("n = %s\n", number.c_str());
	printf("  n-1 = %s\n", (n-1).getNumber().c_str());
	printf("  s = %d\n", s);
	printf("  r = %s\n", r.getNumber().c_str());
	int n_maxitr = atoi(maxitr.c_str());
	assert(r % 2 == 1);
	for (int i = 1; i <= n_maxitr; ++i ){
		int prime = itr.next();
		assert(prime > 0);
		bigInteger a(prime);
		if (a >= n-1) {
			printf("  Itr %d of %d, a = %s (failed)\n,", 
				i, n_maxitr, a.getNumber().c_str());
			printf("Miller-Rabin failure, maxitr is too large\n");
			return;
		}
		bigInteger y = computeY(a, r, n);
		printf("  Itr %d of %d, a = %s, y = %s ",
			i, n_maxitr, a.getNumber().c_str(), y.getNumber().c_str());
		if (y == n-1) {
			printf("(which is n-1)\n");
		} else {
			printf("\n");
		}
		if (y != 1 && y != n-1) {
			for (int j = 1; j <= s-1 && y != n-1; ++j) {
				y = y*y%n;
				printf("    j = %d of %d, y = %s ", j, s-1, y.getNumber().c_str());
				if (y == n-1) {
					printf("(which is n-1)\n");
				} else {
					printf("\n");
				}
				if (y == 1) {
					printf("Miller-Rabin found a strong witness %d\n", prime);
					return;
				}
			}
			if (y != n-1) {
				printf("Miller-Rabin found a strong witness %d\n", prime);
				return;
			}
		}
	}
	printf("Miller-Rabin declares n to be a prime number\n");
}
