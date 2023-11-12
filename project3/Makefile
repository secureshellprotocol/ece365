dijkstra.exe: main.o dijkstra.o heap.o hash.o graph.o
	echo todo update graph.h to match graph.cpp commenst	
	g++ -o dijkstra.exe main.o dijkstra.o heap.o hash.o graph.o

main.o: main.cpp
	g++ -c main.cpp

dijkstra.o: dijkstra.cpp dijkstra.h
	g++ -c dijkstra.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o dijkstraDebug.exe main.cpp dijkstra.cpp heap.cpp hash.cpp graph.cpp

export:
	zip JR_Project3.zip *.cpp *.h Makefile

clean:
	rm -f *.exe *.o *.stackdump *~ *.zip out
	touch out

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
