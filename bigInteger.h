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
	void push_back(char);
	bool operator== (const bigInteger &) const;
	bool operator!= (const bigInteger &) const;
	bigInteger operator+(const bigInteger &) const;
	bigInteger operator-(const bigInteger &) const;
	bool operator< (const bigInteger &) const;
	bool operator> (const bigInteger &) const;
	bool operator>= (const bigInteger &) const;
	bool operator<= (const bigInteger &) const;
	bigInteger operator% (const bigInteger&) const;
	bigInteger operator/ (const bigInteger&) const;
	bigInteger operator* (const bigInteger&) const;
	bigInteger sqrt() const;
	const std::string &getNumber() const;
	static std::pair<std::string, std::string> divide(const std::string&, const std::string&);
	static std::string multiply(const std::string&, const std::string&);
	static std::string add(const std::string&, const std::string&); //both positve
	static std::string subtract(const std::string&, const std::string&); //subtrahend <= minuend
};

std::pair<bigInteger, bigInteger> divmod(const bigInteger&, const bigInteger&);
bigInteger binToBigInteger(const std::string &);

#endif
