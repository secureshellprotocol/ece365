spell.exe: build/spellcheck.o build/hash.o
	g++ -o spell.exe spellcheck.o hash.o

spellcheck.o: spellcheck.cpp hash.h
	mkdir build
	g++ -c spellcheck.cpp 

hash.o: hash.cpp hash.h
	mkdir build
	g++ -c hash.cpp 

debug:
	g++ -g -o spellDebug.exe spellcheck.cpp hash.cpp -Wall -Wextra -Wpedantic

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
