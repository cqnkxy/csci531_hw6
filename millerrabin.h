#ifndef __MILLERRABIN_H_
#define __MILLERRABIN_H_

#include <string>
#include "bigInteger.h"

bigInteger computeY(bigInteger &a, bigInteger &r, bigInteger &n);
bool millerrabin(
	const std::string &number,
	const std::string &maxitr,
	const std::string &primefile,
	bool output=true,
	int addtional_leading_space=0
);

#endif
