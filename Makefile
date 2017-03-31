OBJS = hw6.o utility.o primes.o
CXXFLAGS = -g -Wall
CXX = g++

hw6: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o hw6

utility.o: utility.h utility.cpp
	$(CXX) $(CXXFLAGS) -c utility.cpp
primes.o: primes.h primes.cpp
	$(CXX) $(CXXFLAGS) -c primes.cpp
hw6.o: hw6.cpp
	$(CXX) $(CXXFLAGS) -c hw6.cpp

clean:
	rm -f *.o *.gch hw6
