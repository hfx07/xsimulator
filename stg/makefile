all: strategy_demo
.PHONY: all
strategy_demo: strategy_demo.o StrategyEngine.o ../md/MdEngine.o ../td/TdEngine.o
	g++ -o strategy_demo strategy_demo.o StrategyEngine.o ../md/MdEngine.o ../td/TdEngine.o -L /opt/anaconda2/lib -L ../td -l bz2 -l matchengine -std=c++11
strategy_demo.o: strategy_demo.cpp
	g++ -c strategy_demo.cpp -o strategy_demo.o -I ../md -I ../td -std=c++11
StrategyEngine.o: StrategyEngine.cpp
	g++ -c StrategyEngine.cpp -o StrategyEngine.o -I ../md -I ../td -std=c++11
../md/MdEngine.o: ../md/MdEngine.cpp
	g++ -c ../md/MdEngine.cpp -o ../md/MdEngine.o -I ../md -I ../td -I /opt/anaconda2/include -std=c++11
../td/TdEngine.o: ../td/TdEngine.cpp
	g++ -c ../td/TdEngine.cpp -o ../td/TdEngine.o -I ../md -I ../td -std=c++11

clean:
	rm -rf *.o
	rm -rf ../md/*.o
	rm -rf ../td/*.o
