#ifndef __BIG_INTEGER_H_
#define __BIG_INTEGER_H_

#include <string>
#include <utility>

// A simple positive big integer implementation.
class bigInteger{
private:
	std::string number;
public:
	bigInteger();
	bigInteger(long long);
	bigInteger(const std::string&);
	bigInteger(const bigInteger&);
	bool operator== (const bigInteger &) const;
	bigInteger operator+(const bigInteger &) const;
	bool operator< (const bigInteger &) const;
	bool operator> (const bigInteger &) const;
	bigInteger operator% (const bigInteger&) const;
	bigInteger operator/ (const bigInteger&) const;
	bigInteger operator* (const bigInteger&) const;
	bigInteger sqrt() const;
	const std::string &getNumber() const;
private:
	std::pair<std::string, long long> divide(const std::string&, long long) const;
	std::string multiply(const std::string&, const std::string&) const;
	std::string add(const std::string&, const std::string&) const; //both positve
	std::string subtract(const std::string&, const std::string&) const; //subtrahend <= minuend
};

#endif
