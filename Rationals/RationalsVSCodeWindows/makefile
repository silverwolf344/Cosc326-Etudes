CC = g++

CXXFLAGS = -g3 -Wall


rationals: test.o Integer.o Rational.o
	$(CC) $(CXXFLAGS) -o rationals test.o Integer.o Rational.o

rationals.o: Rational.o Rational.h
	$(CC) $(CXXFLAGS) -c Rational.cpp
Integer.o: Integer.o Integer.h
	$(CC) $(CXXFLAGS) -c Integer.cpp
test.o: test.o
	$(CC) $(CXXFLAGS) -c test.cpp

clean:
	del *.o rationals.exe