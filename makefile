COMP = g++
SOURCES = $(wildcard $(SRC)*.cpp)
OBJECTS = $(subst $(SRC),$(OBJ), $(patsubst %.cpp,%.o, $(SOURCES)))
#SFML_LIB = -L/usr/include -Wl,-rpath=/usr/include
#SFML_LIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
SFML_LIB = -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE = -I/usr/include/
LIB_FLAGS = -Wall -std=c++11 $(SFML_LIB) $(SFML_INCLUDE)
COMP_FLAGS = -Wall -c -std=c++11 $(SFML_LIB)
EXE = CellSpace.exe
BIN = ./bin/
OBJ = ./obj/
SRC = ./src/

all: $(BIN)$(EXE)

$(BIN)$(EXE): $(OBJECTS)
	$(COMP) $(OBJECTS) -o $@ $(LIB_FLAGS)

$(OBJ)%.o: $(SRC)%.cpp
	$(COMP) $(COMP_FLAGS) $< -o $(subst $(SRC), $(OBJ), $@)

clean:
#rm $(wildcard $(OBJ)*.o) && rm $(BIN)$(EXE) && rm $(wildcard $(SRC)*.o)
	rm $(OBJECTS)
	rm $(BIN)$(EXE)
	rm $(wildcard $(SRC)*~)
