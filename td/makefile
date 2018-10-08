all: libmatchengine.so
.PHONY: all
libmatchengine.so: MatchEngine.o
	g++ -o libmatchengine.so -shared MatchEngine.o -std=c++11
MatchEngine.o: MatchEngine.cpp
	g++ -c MatchEngine.cpp -o MatchEngine.o -fPIC -I ../md -std=c++11

clean:
	rm MatchEngine.o
