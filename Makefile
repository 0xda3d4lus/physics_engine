CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = main.cpp mod/laws.cpp mod/object.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = out

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
