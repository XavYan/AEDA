CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BUILD		:= build
SRC	    	:= src
INCLUDE 	:= include

LIBRARIES	:=
EXECUTABLE	:= main


all: $(BUILD)/$(EXECUTABLE)

run: clean all
	clear
	./$(BUILD)/$(EXECUTABLE)

$(BUILD)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(BUILD) $^ -o $@ $(LIBRARIES)

clean:
	-rm $(BUILD)/main