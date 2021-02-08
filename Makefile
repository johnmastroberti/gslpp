CXX = g++
LD = g++

IFLAGS = -Iinclude
WFLAGS = -Wall -Wextra -Wpedantic -Wshadow
CXXFLAGS = -std=c++20 $(IFLAGS) $(WFLAGS)

libsrc = src/vector.cpp
libobj = $(libsrc:src/%.cpp=obj/%.o)

.EXTRA_PREREQS = Makefile

default: lib

test: test.out
	./test.out

test.out: test/main.o lib
	$(LD) -o $@ -Llib $< -lgsl -lgslcblas -lgslpp

test/main.o: test/main.cpp include/vector.hpp
	$(CXX) -o $@ $(CXXFLAGS) -c $<


# static library

lib: lib/libgslpp.a

lib/libgslpp.a: $(libobj)
	ar rcs $@ $^

# object files

obj/%.o: src/%.cpp
	$(CXX) -o $@ $(CXXFLAGS) -c $<

obj/vector.o: src/vector.cpp include/vector.hpp


.PHONY: lib default
