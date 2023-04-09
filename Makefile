main: driver.o
	g++ -std=c++11 bet.cpp driver.cpp -o driver.x

driver.o: 
	g++ -std=c++11 -c driver.cpp

bet.o:
	g++ -std=c++11 -c bet.cpp
