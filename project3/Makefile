dijkstra.exe: main.o heap.o hash.o graph.o
	echo todo update graph.h to match graph.cpp commenst	
	g++ -o dijkstra.exe main.o heap.o hash.o graph.o

main.o: main.cpp
	g++ -c main.cpp

graph.o: graph.cpp graph.h hash.cpp hash.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

hard: clean dijkstra.exe

debug:
	g++ -g -o dijkstraDebug.exe main.cpp heap.cpp hash.cpp graph.cpp

export: clean
	zip JR_Project3.zip *.cpp *.h Makefile

clean:
	rm -f *.exe *.o *.stackdump *~ *.zip out
	touch out

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
