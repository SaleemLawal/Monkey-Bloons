CXX = g++
CXXFLAGS = -Wall -g
OBJECTS = Game.o Bloon.o Monkey.o Basic.o Bomb.o Dart.o Boomerang.o
IODIR =../../proj4_IO

main: $(OBJECTS) main.cpp
	$(CXX) $(CXXFLAGS) $(OBJECTS) main.cpp -o main

Game.o: Game.h Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Basic.o: Basic.cpp Basic.h Bloon.o
	$(CXX) $(CXXFLAGS) -c Basic.cpp

Bomb.o: Bomb.cpp Bomb.h Monkey.o
	$(CXX) $(CXXFLAGS) -c Bomb.cpp

Dart.o: Dart.cpp Dart.h Monkey.o
	$(CXX) $(CXXFLAGS) -c Dart.cpp

Boomerang.o: Boomerang.h Boomerang.cpp Monkey.o
	$(CXX) $(CXXFLAGS) -c Boomerang.cpp

Monkey.o: Monkey.cpp Monkey.h
	$(CXX) $(CXXFLAGS) -c Monkey.cpp

Bloon.o: Bloon.cpp Bloon.h
	$(CXX) $(CXXFLAGS) -c Bloon.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./main

val:
	valgrind ./main

debug:
	gdb gdbarg1 --args ./main

