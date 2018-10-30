CXX=g++
EXEC=predatorPreyGame
SOURCES=predPrey.cpp game.cpp critter.cpp ant.cpp db.cpp menu.cpp utils.cpp
OBJECTS=$(SOURCES:.cpp=.o)
CXXFLAGS=-std=c++11 -c -g -Wall -pedantic-errors
LFLAGS=-std=c++11 -g
HEADERS=game.hpp critter.hpp ant.hpp db.hpp menu.hpp utils.hpp

$(EXEC) : $(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS) -o $(EXEC)

predPrey.o : $(HEADERS) predPrey.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) predPrey.cpp

game.o : $(HEADERS) game.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) game.cpp

critter.o : $(HEADERS) critter.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) critter.cpp

ant.o : $(HEADERS) ant.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) ant.cpp

db.o : $(HEADERS) db.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) db.cpp

menu.o : menu.hpp menu.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) menu.cpp

utils.o : utils.hpp utils.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) utils.cpp

clean :
	rm $(EXEC) $(OBJECTS) *.gch
