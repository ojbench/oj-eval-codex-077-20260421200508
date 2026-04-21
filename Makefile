all:
	g++ -std=gnu++14 -O2 -pipe -static -s -o code main.cpp
clean:
	rm -f code
