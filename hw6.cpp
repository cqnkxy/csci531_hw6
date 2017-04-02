#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "utility.h"
#include "primes.h"
#include "trialdiv.h"
#include "millerrabin.h"
#include "rndsearch.h"
#include "maurer.h"

using namespace std;

void malformed_command() {
	const string USAGE = 
		"\n\thw6 primes -n=maxval"
	    "\n\thw6 trialdiv -n=number -p=primesfile"
	    "\n\thw6 millerrabin -n=number -t=maxitr -p=primesfile"
	    "\n\thw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile"
	    "\n\thw6 maurer -k=numbits -p=primesfile -r=rndfile\n";

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

void parse_trialdiv(int argc, char *argv[]) {
	if (argc != 4) {
		malformed_command();
	}
	string number, primesfile;
	for (int i = 2; i <= 3; ++i) {
		string opt(argv[i]);
		if (opt.substr(0, 3) == "-n=") {
			number = opt.substr(3, -1);
		} else if (opt.substr(0, 3) == "-p=") {
			primesfile = opt.substr(3, -1);
		} else {
			malformed_command();
		}
	}
	trialdiv(number, primesfile);
}

void parse_millerrabin(int argc, char *argv[]) {
	if (argc != 5) {
		malformed_command();
	}
	string number, maxitr, primesfile;
	for (int i = 2; i <= 4; ++i) {
		string opt(argv[i]);
		if (opt.substr(0, 3) == "-n=") {
			number = opt.substr(3, -1);
		} else if (opt.substr(0, 3) == "-t=") {
			maxitr = opt.substr(3, -1);
		} else if (opt.substr(0, 3) == "-p=") {
			primesfile = opt.substr(3, -1);
		} else {
			malformed_command();
		}
	}
	millerrabin(number, maxitr, primesfile);
}

void parse_rndsearch(int argc, char *argv[]) {
	if (argc != 6) {
		malformed_command();
	}
	string numbits, maxitr, primesfile, rndfile;
	for (int i = 2; i <= 5; ++i) {
		string opt(argv[i]);
		if (opt.substr(0, 3) == "-k=") {
			numbits = opt.substr(3, -1);
		} else if (opt.substr(0, 3) == "-t=") {
			maxitr = opt.substr(3, -1);
		} else if (opt.substr(0, 3) == "-p=") {
			primesfile = opt.substr(3, -1);
		} else if (opt.substr(0, 3) == "-r=") {
			rndfile = opt.substr(3, -1);
		} else {
			malformed_command();
		}
	}
	rndsearch(numbits, maxitr, primesfile, rndfile);
}

void parse_maurer(int argc, char *argv[]) {
	if (argc != 5) {
		malformed_command();
	}
	string numbits, primesfile, rndfile;
	for (int i = 2; i <= 4; ++i) {
		string opt(argv[i]);
		if (opt.substr(0, 3) == "-k=") {
			numbits = opt.substr(3, -1);
		} else if (opt.substr(0, 3) == "-p=") {
			primesfile = opt.substr(3, -1);
		} else if (opt.substr(0, 3) == "-r=") {
			rndfile = opt.substr(3, -1);
		} else {
			malformed_command();
		}
	}
	maurer(numbits, primesfile, rndfile);
}

void parse_cmd_run(int argc, char *argv[]) {
	if (argc < 3) {
		malformed_command();
	} else if (strcmp(argv[1], "primes") == 0) {
		parse_primes(argc, argv);
	} else if (strcmp(argv[1], "trialdiv") == 0){
		parse_trialdiv(argc, argv);
	} else if (strcmp(argv[1], "millerrabin") == 0) {
		parse_millerrabin(argc, argv);
	} else if (strcmp(argv[1], "rndsearch") == 0) {
		parse_rndsearch(argc, argv);
	} else if (strcmp(argv[1], "maurer") == 0) {
		parse_maurer(argc, argv);
	} else {
		malformed_command();
	}
}

int main(int argc, char *argv[]) 
{
	parse_cmd_run(argc, argv);
	return 0;
}
