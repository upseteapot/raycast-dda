CXX    := g++
FLAGS  := -Wall -Wextra -std=c++17
LIBS   := -lsfml-graphics -lsfml-system -lsfml-window 
TARGET := main

all: clean $(TARGET)

$(TARGET): ./src/*.cpp ./src/*/*.cpp
	$(CXX) $(FLAGS) $(LIBS) $^ -o $@ -I./include/

clean:
	rm -f $(TARGET)

