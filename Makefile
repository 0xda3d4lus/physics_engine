CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = cli.cpp mod/laws.cpp mod/object.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = cli

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
