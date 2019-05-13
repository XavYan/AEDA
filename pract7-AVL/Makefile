CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BUILD		:= build
SRC	    	:= src
INCLUDE 	:= include

LIBRARIES	:=
EXECUTABLE	:= main


all: demos est

rund:
	clear
	./$(BUILD)/demos

rune:
	clear
	./$(BUILD)/est

demos: clean
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(BUILD) $(SRC)/DNI.cpp $(SRC)/main_demos.cpp $(SRC)/Contador.cpp -o $(BUILD)/$@ $(LIBRARIES)

est: clean
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(BUILD) $(SRC)/DNI.cpp $(SRC)/main_est.cpp $(SRC)/Contador.cpp -o $(BUILD)/$@ $(LIBRARIES)


clean:
	-rm $(BUILD)/est
	-rm $(BUILD)/demos
