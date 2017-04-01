#ifndef __MILLERRABIN_H_
#define __MILLERRABIN_H_

#include <string>
#include "bigInteger.h"

bigInteger computeY(bigInteger &a, bigInteger &r, bigInteger &n);
void millerrabin(
	const std::string &number,
	const std::string &maxitr,
	const std::string &primefile
);

#endif
