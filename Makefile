OBJS = utility.o primes.o bigInteger.o trialdiv.o millerrabin.o \
	rndsearch.o
CXXFLAGS = -g -Wall
CXX = g++

hw6: $(OBJS) hw6.o 
	$(CXX) $(CXXFLAGS) $(OBJS) hw6.o -o hw6
test: $(OBJS) test.o
	$(CXX) -g -W -std=c++11 $(OBJS) test.o -o test

rndsearch.o: rndsearch.h rndsearch.cpp
	$(CXX) $(CXXFLAGS) -c rndsearch.cpp
millerrabin.o: millerrabin.h millerrabin.cpp
	$(CXX) $(CXXFLAGS) -c millerrabin.cpp
utility.o: utility.h utility.cpp
	$(CXX) $(CXXFLAGS) -c utility.cpp
primes.o: primes.h primes.cpp
	$(CXX) $(CXXFLAGS) -c primes.cpp
bigInteger.o: bigInteger.h bigInteger.cpp
	$(CXX) $(CXXFLAGS) -c bigInteger.cpp
hw6.o: hw6.cpp
	$(CXX) $(CXXFLAGS) -c hw6.cpp
trialdiv.o: trialdiv.h trialdiv.cpp
	$(CXX) $(CXXFLAGS) -c trialdiv.cpp
test.o: test.cpp
	$(CXX) -g -W -std=c++11 -c test.cpp

clean:
	rm -f *.o *.gch hw6 test
