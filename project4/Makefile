CXX      ?= g++
CXXFLAGS += -g -Wall -Wextra -Wpedantic -std=c++11


all: merge.exe


merge.exe: main.o merge.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

merge.o: merge.cpp merge.h 
	$(CXX) $(CXXFLAGS) -c merge.cpp

.PHONY: hard
hard: clean merge.exe

.PHONY: export
export: clean
	zip JR_Project3.zip *.cpp *.h Makefile

.PHONY: clean
clean:
	@rm -vf *.exe *.o *.stackdump *~ *.zip out
