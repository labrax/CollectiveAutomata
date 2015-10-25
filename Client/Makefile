
OBJ_DIR := obj
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

LD_FLAGS := -Wall -g -lsfml-system -lsfml-window -lsfml-graphics -lGL 
CC_FLAGS := -Wall -g

all: client

client: $(OBJ_FILES)
	g++ $^ $(LD_FLAGS) -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	g++ $< $(CC_FLAGS) -c -o $@

$(OBJ_FILES): | $(OBJ_DIR) 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
   
clean:
	rm $(OBJ_FILES) client