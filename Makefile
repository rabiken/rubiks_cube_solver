# compiler
CXX = g++
# flags
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 #-fsanitize=address -g

# source files
SRCS = src

all: main visualizer

test: test_print2D test_distance

%.o: $(SRCS)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

visualizer: $(SRCS)/visualizer.cpp cube.o face.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system
main: $(SRCS)/main.cpp cube.o face.o distanceManager.o solver.o node.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_print2D: $(SRCS)/test_print2D.cpp cube.o face.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test_distance: $(SRCS)/test_distance.cpp distanceManager.o cube.o face.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf test_print2D *dSYM *.o test_distance main visualizer
