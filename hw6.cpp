#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "utility.h"
#include "primes.h"

using namespace std;

void malformed_command() {
	const string USAGE = 
		"\t\nhw6 primes -n=maxval"
	    "\t\nhw6 trialdiv -n=number -p=primesfile"
	    "\t\nhw6 millerrabin -n=number -t=maxitr -p=primesfile"
	    "\t\nhw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile"
	    "\t\nhw6 maurer -k=numbits -p=primesfile -r=rndfile";

	cerr << "Malformed command. Use it as:" << endl << USAGE << endl;
	exit(1);
}

void parse_primes(int argc, char *argv[]) {
	if (argc != 3 || strncmp(argv[2], "-n=", 3) != 0) {
		malformed_command();
	}
	if (!all_dec(argv[2]+3)) {
		fatal("Invalid maxval! Only [0-9] allowed!\n");
	}
	int maxval = atoi(argv[2]+3);
	if (maxval < 2 || maxval > (1 << 24)) {
		fatal("Invalid maxval! maxval must be in the range [2, 2^24]\n");
	}
	primes(maxval);
}

void parse_cmd_run(int argc, char *argv[]) {
	if (argc < 3) {
		malformed_command();
	} else if (strcmp(argv[1], "primes") == 0) {
		parse_primes(argc, argv);
	} else {
		malformed_command();
	}
}

int main(int argc, char *argv[]) 
{
	parse_cmd_run(argc, argv);
	return 0;
}
