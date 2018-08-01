all: reviiot

reviiot: bin/Card.o bin/Player.o bin/Deck.o bin/Game.o bin/Hand.o bin/Reviiyot.o  
	g++ -o bin/reviiot bin/Card.o bin/Player.o bin/Deck.o bin/Game.o bin/Hand.o bin/Reviiyot.o 

bin/Card.o: src/Card.cpp include/Card.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Card.o src/Card.cpp
 
bin/Player.o: src/Player.cpp include/Player.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Player.o src/Player.cpp
  
bin/Deck.o: src/Deck.cpp include/Deck.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Deck.o src/Deck.cpp 

bin/Game.o: src/Game.cpp include/Game.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Game.o src/Game.cpp
 
bin/Hand.o: src/Hand.cpp include/Hand.h
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Hand.o src/Hand.cpp
 
bin/Reviiyot.o: src/Reviiyot.cpp 
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Reviiyot.o src/Reviiyot.cpp

clean: 
	rm -f bin/*