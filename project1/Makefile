spell.exe: spellcheck.o hash.o
	g++ -o spell.exe spellcheck.o hash.o

spellcheck.o: spellcheck.cpp hash.h
	g++ -c spellcheck.cpp 

hash.o: hash.cpp hash.h
	g++ -c hash.cpp 

debug:
	g++ -g -o spellDebug.exe spellcheck.cpp hash.cpp -Wall -Wextra -Wpedantic

export:
	zip JR_Project1.zip *.cpp *.h Makefile

clean:
	rm -f *.exe *.o *.stackdump *~ JR_Project1.zip out
	touch out

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
