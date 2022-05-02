main: lab7functionO mainO
	g++ -o main main.o lab7functions.o

lab7functionO: lab7functions.cpp lab7.h
	g++ -c lab7functions.cpp
mainO: main.cpp lab7.h
	g++ -c main.cpp

clean: 
	rm -f main.exe main.o lab7functions.o