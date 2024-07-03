CXX = g++
CXXFLAGS = -Wall -g -Wno-builtin-declaration-mismatch

.PHONY: all clean catan test 

OBJECTS = Board.o Catan.o demo.o Cross_Section.o Tile.o Player.o Piece.o Card.o
ST=Board.cpp Catan.cpp Cross_Section.cpp Tile.cpp Player.cpp Piece.cpp Card.cpp
OBJECTSTEST=$(subst .cpp,.o,$(SOURCESTEST))
SOURCESTEST=TestCounter.cpp Test.cpp 
OT= $(subst .cpp,.o,$(ST))

all: demo

demo: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o $(OT)
	$(CXX) $(CXXFLAGS) $^ -o test

catan: demo
	./demo

tidy:
	clang-tidy Board.cpp Catan.cpp demo.cpp Cross_Section.cpp Tile.cpp Player.cpp Piece.cpp Card.cpp -checks=bugprone-*,g++-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f *.o demo

