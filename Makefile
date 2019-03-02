# Project
PROJECT = chess
BIN = $(PROJECT)


# Compiler
CXX = g++
CFLAGS = -Wall -Wextra -c --std=c++17 -g -DDEBUG

# Includes
INCLUDE = -Iinclude

# Linker

LFLAGS = $(shell command -v g++-7.3 >/dev/null 2>&1 && echo -n "-static-libstdc++")

# Folders

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

# Sources
APP_SRC = $(wildcard $(SRC_DIR)/*.cpp)
APP_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.cpp, %.o, $(APP_SRC))))

CONTROLLER_SRC = $(wildcard $(SRC_DIR)/controller/*.cpp)
CONTROLLER_OBJ = $(addprefix $(OBJ_DIR)/controller/, $(notdir $(patsubst %.cpp, %.o, $(CONTROLLER_SRC))))

MODEL_SRC = $(wildcard $(SRC_DIR)/model/*.cpp)
MODEL_OBJ = $(addprefix $(OBJ_DIR)/model/, $(notdir $(patsubst %.cpp, %.o, $(MODEL_SRC))))

all: app

app: $(APP_OBJ) $(CONTROLLER_OBJ) $(MODEL_OBJ)
	 $(CXX) $^ -o $(BIN_DIR)/$(BIN) $(LFLAGS)

# main.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)
	$(CXX) $(INCLUDE) $(CFLAGS) $< -o $@

# controller/*.o
$(OBJ_DIR)/controller/%.o: $(SRC_DIR)/controller/%.cpp
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)/controller
	$(CXX) $(INCLUDE) $(CFLAGS) $< -o $@

# model/*.o
$(OBJ_DIR)/model/%.o: $(SRC_DIR)/model/%.cpp
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)/model
	$(CXX) $(INCLUDE) $(CFLAGS) $< -o $@

run:
	@make all && ./$(BIN_DIR)/$(BIN)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: app