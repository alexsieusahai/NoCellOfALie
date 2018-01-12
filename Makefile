solveEquation: solveEquation.o printTables.o
	g++ solveEquation.o printTables.o -o solveEquation -std=c++11

solveEquation.o: solveEquation.cpp
	g++ -c solveEquation.cpp -std=c++11

printTables.o: printTables.cpp printTables.h
	g++ -c printTables.cpp -std=c++11

clean:
	rm *.o
