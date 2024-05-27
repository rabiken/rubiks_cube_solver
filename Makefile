# compiler
CXX = g++
# flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 #-fsanitize=address -g

all: main visualizer

test: test_print2D test_distance

*.o: *.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

visualizer: visualizer.cpp cube.o face.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system
main: main.cpp cube.o face.o distanceManager.o solver.o node.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_print2D: test_print2D.cpp cube.o face.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_distance: test_distance.cpp distanceManager.o cube.o face.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf test_print2D *dSYM *.o test_distance main visualizer
