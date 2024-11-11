all: stats2 rhymes

stats2: stats2.cpp
	g++ -o stats2 stats2.cpp -std=c++11 -Wall

rhymes: rhymes.cpp
	g++ -o rhymes rhymes.cpp
	
clean:
	rm -f *.o stats2 rhymes
