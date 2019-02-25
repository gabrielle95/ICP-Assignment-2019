# Project
PROJECT = chess
BIN = $(PROJECT)


# Compiler
CXX = g++
CFLAGS = -Wall -Wextra -c --std=c++17 -g -DDEBUG

# Includes
INCLUDE = -Iinclude

# Linker

LFLAGS =

# Folders

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

# Sources
APP_SRC = $(wildcard $(SRC_DIR)/*.cpp)
APP_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.cpp, %.o, $(APP_SRC))))



all: app

app: $(APP_OBJ)
	 $(CXX) $^ -o $(BIN_DIR)/$(BIN) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)
	$(CXX) $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: app