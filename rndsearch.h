#ifndef __RNDSEARCH_H_
#define __RNDSEARCH_H_

#include <string>
#include <iostream>

bigInteger RndOddNum(int k, std::istream &in);
void rndsearch(
	const std::string &numbits,
	const std::string &maxitr,
	const std::string &primesfile,
	const std::string &rndfile
);

#endif
