OBJS = utility.o primes.o bigInteger.o trialdiv.o millerrabin.o \
	rndsearch.o maurer.o
CXXFLAGS = -g -Wall
CXX = g++

hw6: $(OBJS) hw6.o 
	$(CXX) $(CXXFLAGS) $(OBJS) hw6.o -o hw6 -lssl -lcrypto -L/usr/local/opt/openssl/lib
test: $(OBJS) test.o
	$(CXX) -g -W -std=c++11 $(OBJS) test.o -o test -lssl -lcrypto -L/usr/local/opt/openssl/lib

maurer.o: maurer.h maurer.cpp
	$(CXX) $(CXXFLAGS) -c maurer.cpp
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
	$(CXX) $(CXXFLAGS) -c trialdiv.cpp -I/usr/local/opt/openssl/include
test.o: test.cpp
	$(CXX) -g -W -std=c++11 -c test.cpp

clean:
	rm -f *.o *.gch hw6 test
