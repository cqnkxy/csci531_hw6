#include <string>
#include <utility>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "bigInteger.h"
#include "utility.h"

using namespace::std;

bigInteger::bigInteger() {
	number = "0";
}

bigInteger::bigInteger(long long num) {
	char buf[50];
	sprintf(buf, "%lld", num);
	number = string(buf);
}

bigInteger::bigInteger(const std::string &num) {
	number = num;
}

bigInteger::bigInteger(const bigInteger &bigInt) {
	this->number = bigInt.getNumber();
}

void bigInteger::push_back(char ch) {
	this->number += ch;
}

const string &bigInteger::getNumber() const {
	return number;
}

bool bigInteger::operator== (const bigInteger &bigInt) const {
	return this->number == bigInt.getNumber();	
}

bool bigInteger::operator!= (const bigInteger &bigInt) const {
	return !(*this == bigInt);
}

bool bigInteger::operator< (const bigInteger &bigInt) const {
	size_t sz1 = this->number.size(), sz2 = bigInt.getNumber().size();
	if (sz1 != sz2) {
		return sz1 < sz2;
	}
	return this->number < bigInt.getNumber();
}

bool bigInteger::operator<= (const bigInteger &bigInt) const {
	return !(*this > bigInt);
}

bool bigInteger::operator>= (const bigInteger &bigInt) const {
	return !(*this < bigInt);
}

bool bigInteger::operator> (const bigInteger &bigInt) const {
	return !(*this == bigInt || *this < bigInt);
}

bigInteger bigInteger::operator/ (const bigInteger &bigInt) const {
	pair<string, string> res = divide(this->getNumber(), bigInt.getNumber());
	return res.first;
}

bigInteger bigInteger::operator% (const bigInteger &bigInt) const {
	pair<string, string> res = divide(this->getNumber(), bigInt.getNumber());
	return res.second;
}

bigInteger bigInteger::operator* (const bigInteger &bigInt) const {
	return multiply(this->getNumber(), bigInt.getNumber());
}

bigInteger bigInteger::operator+(const bigInteger &bigInt) const {
	return add(this->number, bigInt.getNumber());
}

bigInteger bigInteger::operator-(const bigInteger &bigInt) const {
	return subtract(this->number, bigInt.getNumber());
}

bigInteger bigInteger::sqrt() const {
	if (*this == 0 || *this == 1) {
		return *this;
	}
	bigInteger beg(0), end(*this), res;
	while (beg < end) {
		bigInteger mid = (beg + end) / 2;
		if (mid * mid > *this) {
			end = mid;
		} else {
			res = mid;
			beg = mid+1;
		}
	}
	return res;
}

pair<string, string> bigInteger::divide(const string &dividend, const string &divisor) {
	assert(divisor.size() != 0);
	if (bigInteger(dividend) < bigInteger(divisor)) {
		return make_pair("0", dividend);
	}
	bigInteger b_dividend(dividend), b_divisor(divisor);
	bigInteger b_quotient, b_remainder = dividend.substr(0, divisor.size()-1);
	for (size_t i = divisor.size()-1; i < dividend.size(); ++i) {
		if (b_remainder == 0) {
			b_remainder = b_remainder + (dividend[i]-'0');
		} else {
			b_remainder.push_back(dividend[i]);
		}
		int beg = 0, end = 9, q;
		while (beg <= end) {
			int m = (beg + end) / 2;
			if (b_remainder >= b_divisor * m) {
				q = m;
				beg = m+1;
			} else {
				end = m-1;
			}
		}
		b_remainder = b_remainder - b_divisor * q;
		if (b_quotient == 0) {
			b_quotient = b_quotient + q;
		} else {
			b_quotient.push_back('0' + q);
		}
	}
	return make_pair(b_quotient.getNumber(), b_remainder.getNumber());
}

string bigInteger::multiply(const string &n1, const string &n2) {
	vector<int> ans(n1.size() + n2.size(), 0);
    int sz1 = n1.size(), sz2 = n2.size();
	for (int i = 0; i < sz1; ++i) {
		for (int j = 0; j < sz2; ++j) {
			ans[i+j] += (n1[sz1-i-1]-'0') * (n2[sz2-1-j]-'0');
			ans[i+j+1] += ans[i+j] / 10;
			ans[i+j] %= 10;
		}
	}
	while (!ans.empty() && ans.back() == 0) {
		ans.pop_back();
	}
	string res;
	for (int i = (int)ans.size()-1; i >= 0; --i) {
		res += '0'+ans[i];
	}
	return !res.empty() ? res : "0"; 
}

string bigInteger::add(const string &n1, const string &n2) {
	vector<int> ans;
	int sz1 = n1.size(), sz2 = n2.size();
	int i = 0, j = 0, carry = 0;
	while (i < sz1 || j < sz2) {
		if (i < sz1) {
			carry += n1[sz1-(i++)-1] - '0';
		}
		if (j < sz2) {
			carry += n2[sz2-(j++)-1] - '0';
		}
		ans.push_back(carry % 10);
		carry /= 10;
	}
	if (carry) {
		ans.push_back(carry);
	}
	while (!ans.empty() && ans.back() == 0) {
		ans.pop_back();
	}
	string res;
	for (int i = (int)ans.size()-1; i >= 0; --i) {
		res += '0'+ans[i];
	}
	return !res.empty() ? res : "0";
}

string bigInteger::subtract(const string &n1, const string &n2) {
	if (bigInteger(n1) < bigInteger(n2)) {
		fatal("bigInteger subtract: %s has to be bigger than %s\n", n1.c_str(), n2.c_str());
	}
	vector<int> ans;
	int sz1 = n1.size(), sz2 = n2.size();
	int i = 0, j = 0, carry = 0;
	while (i < sz1 || j < sz2 || carry) {
		int tmp = n1[sz1-(i++)-1] - '0' - carry;
		if (j < sz2) {
			tmp -= n2[sz2-(j++)-1] - '0';
		}
		int n_carry = tmp < 0;
		ans.push_back(tmp >= 0 ? tmp : tmp + 10);
		carry = n_carry;
	}
	while (!ans.empty() && ans.back() == 0) {
		ans.pop_back();
	}
	string res;
	for (int i = (int)ans.size()-1; i >= 0; --i) {
		res += '0'+ans[i];
	}
	return !res.empty() ? res : "0";
}

pair<bigInteger, bigInteger> divmod(const bigInteger &dividend, const bigInteger &divisor){
	pair<string, string> res = bigInteger::divide(dividend.getNumber(), divisor.getNumber());
	return make_pair(bigInteger(res.first), bigInteger(res.second));
}

bigInteger binToBigInteger(const string &bin) {
	bigInteger ans(0);
	for (size_t i = 0; i < bin.size(); ++i) {
		ans = ans * 256 + (unsigned char)bin[i];
	}
	return ans;
}
