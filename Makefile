main:	main.o laby.o matrices.o svg.o parcours.o
		g++ main.o laby.o matrices.o svg.o parcours.o -o main

laby.o:	laby.cpp
		g++ -c laby.cpp

matrices.o:	matrices.cpp
		g++ -c matrices.cpp

svg.o:	svg.cpp
		g++ -c svg.cpp

parcours.o:	parcours.cpp
		g++ -c parcours.cpp