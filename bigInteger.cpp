#include <string>
#include <utility>
#include <vector>
#include <cstdlib>
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
	pair<string, long long> res = divide(this->getNumber(), atol(bigInt.getNumber().c_str()));
	return res.first;
}

bigInteger bigInteger::operator% (const bigInteger &bigInt) const {
	pair<string, long long> res = divide(this->getNumber(), atol(bigInt.getNumber().c_str()));
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

pair<string, long long> bigInteger::divide(const string &dividend, long long divisor) {
	if (dividend.size() == 0) {
		return make_pair("0", 0);
	}
	long long remainder = 0;
	string quotient;
	for(int i = 0; i < (int)dividend.size(); ++i) {
		remainder = (remainder * 10) + (dividend[i] - '0');
		quotient += remainder / divisor + '0';
		if (quotient.front() == '0') {
			// of size 1 and is "0"
			quotient.pop_back();
		}
		remainder %= divisor;
	}
	if(quotient.length() == 0) {
		quotient = "0";
	}
	return make_pair(quotient, remainder);
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
	if (n1 < n2) {
		fatal("%s has to be bigger than %s", n1.c_str(), n2.c_str());
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
	pair<string, long long> res = bigInteger::divide(dividend.getNumber(), atol(divisor.getNumber().c_str()));
	return make_pair(bigInteger(res.first), bigInteger(res.second));
}
