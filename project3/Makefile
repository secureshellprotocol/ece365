CXX      ?= g++
CXXFLAGS += -g -Wall -Wextra -Wpedantic -std=c++11


all: dijkstra.exe


dijkstra.exe: main.o heap.o hash.o graph.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

graph.o: graph.cpp graph.h hash.cpp hash.h
	$(CXX) $(CXXFLAGS) -c graph.cpp

heap.o: heap.cpp heap.h
	$(CXX) $(CXXFLAGS) -c heap.cpp

hash.o: hash.cpp hash.h
	$(CXX) $(CXXFLAGS) -c hash.cpp

hard: clean dijkstra.exe

.PHONY: export
export: clean
	zip JR_Project3.zip *.cpp *.h Makefile

.PHONY: clean
clean:
	@rm -vf *.exe *.o *.stackdump *~ *.zip out
	touch out
