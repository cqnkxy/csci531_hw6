# USC CSCI531 HW6

Generate primes numebrs.

## Compile

type `make` or `make hw6` to generate executable.
type `make clean` to clear up *.o file and executable.

## Command

### sieve of Eratosthenes: hw6 primes -n=maxval
Generate all prime numbers less than or equal to maxval. maxval must be between 2 and 2<sup>24</sup>>, inclusive. You can use the sieve of Eratosthenes to generate the needed prime numbers.

Since the sieve of Eratosthenes uses an array of maxval integers whose values can only be 0 or 1, please be memory efficient and use only maxval bits (i.e., ceil(maxval/8) bytes) for the array.

### trial divison: hw6 trialdiv -n=number -p=primesfile
Test the primality of number using trial division by trying sequentially all small prime numbers from 2 to floor(sqrt(number)), inclusive. primesfile conforms to the [primesfile format](http://merlot.usc.edu/cs531-s17/homeworks/hw6/#format) and must be used as the source of small prime numbers. There is no limit how large number can be.

### miller rabin: hw6 millerrabin -n=number -t=maxitr -p=primesfile
Test the primality of number using Miller-Rabin specified [here](http://merlot.usc.edu/cs531-s17/homeworks/hw6/#millerrabin) with security parameter maxitr. There is no limit how large number can be.

### random search: hw6 rndsearch -k=numbits -t=maxitr -p=primesfile -r=rndfile
Generate a numbits-bit probable prime using the Random-Search(numbits,maxitr) algorithm specified [here](http://merlot.usc.edu/cs531-s17/homeworks/hw6/#rndsearch) with security parameter maxitr.

### maurer: hw6 maurer -k=numbits -p=primesfile -r=rndfile
Generate a numbits-bit provable prime using the Maurer(numbits) algorithm specified [here](http://merlot.usc.edu/cs531-s17/homeworks/hw6/#maurer).
