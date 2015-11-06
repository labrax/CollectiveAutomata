
OBJ_DIR := obj
CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

LD_FLAGSx86 := -LSFML-2.3.2x86/lib -m32
CC_FLAGSx86 := -ISFML-2.3.2x86/include -m32

LD_FLAGSx64 := -LSFML-2.3.2x64/lib
CC_FLAGSx64 := -ISFML-2.3.2x64/include

LD_VERSION := $(LD_FLAGSx64)
CC_VERSION := $(CC_FLAGSx64)

LD_FLAGS := -Wall -g $(LD_VERSION) -ljpeg -lxcb-util -lxcb-image -lsfml-system -lsfml-window -lsfml-graphics -fopenmp
CC_FLAGS := -Wall -g $(CC_VERSION) -fopenmp

all: client

client: $(OBJ_FILES)
	g++ $^ $(LD_FLAGS) -o $@

run: client
	./client

$(OBJ_DIR)/%.o: src/%.cpp
	g++ $< $(CC_FLAGS) -c -o $@

$(OBJ_FILES): | $(OBJ_DIR) 

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
   
clean:
	rm $(OBJ_FILES) client
