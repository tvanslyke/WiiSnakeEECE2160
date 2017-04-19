objects = Main.o  BaseRNG.o WiiMote.o  SnakeBoard.o Segment.o Snake.o KeyBoard.o SnakeGame.o
headers = EventReader.h UniformRNG.h Utilities.h


wiisnake: $(headers) $(objects)
	g++ -lpthread -std=c++11 $(headers) $(objects) -o wiisnake
	make clean
	
Main.o: SnakeGame.h Main.cpp
	g++ -c -std=c++11  Main.cpp

Segment.o: Segment.h Segment.cpp
	g++ -c -std=c++11  Segment.cpp
	
Snake.o:  Utilities.h Segment.h Snake.h Snake.cpp
	g++ -c -std=c++11  Snake.cpp	

BaseRNG.o: BaseRNG.h BaseRNG.cpp
	g++ -c -std=c++11  BaseRNG.cpp
	
SnakeBoard.o: SnakeBoard.h UniformRNG.h Snake.h SnakeBoard.cpp
	g++ -c -std=c++11  SnakeBoard.cpp
	
WiiMote.o: EventReader.h WiiMote.h WiiMote.cpp
	g++ -c -std=c++11  WiiMote.cpp
	
KeyBoard.o: EventReader.h KeyBoard.h KeyBoard.cpp
	g++ -c -std=c++11  KeyBoard.cpp
	

SnakeGame.o: WiiMote.h KeyBoard.h SnakeGame.h EventReader.h SnakeBoard.cpp
	g++ -c  -lpthread -std=c++11 SnakeBoard.cpp
	

clean: 
	rm $(objects)



	
