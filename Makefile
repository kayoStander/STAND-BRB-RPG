CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Werror -Wsign-conversion -Wconversion -O3
LIBS = -lncurses

TARGET = out

.SILENT: all
all: $(TARGET)

$(TARGET): *.cpp *.hpp
	@$(CXX) $(CXXFLAGS) -o $@ *.cpp $(LIBS)
	@./$(TARGET)
	@rm -f ./$(TARGET)

clean:
	@rm -f $(TARGET)
