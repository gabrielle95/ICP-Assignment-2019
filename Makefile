# Project
PROJECT = chess
BIN = $(PROJECT)

# Doxygen
DOXYFILE=Doxyfile

# Zip file
ZIP_FILE=xpacak01-xlanic04.zip

# Compiler
CXX = g++
CFLAGS = -c --std=c++17 -g -DDEBUG
QFLAGS =
QFLAGS_DEBUG = CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug

# Includes
INCLUDE = -Iinclude

# Linker
LFLAGS = -lpthread
LFLAGS += $(shell command -v g++-7.3 >/dev/null 2>&1 && echo -n "-static-libstdc++")

# Folders

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
GUI_DIR = gui
GUI_QMAKE = gui_qmake
DOXY_DIR=doc

# Sources
APP_SRC = $(wildcard $(SRC_DIR)/view/cli/*.cpp)
APP_OBJ = $(addprefix $(OBJ_DIR)/view/cli/, $(notdir $(patsubst %.cpp, %.o, $(APP_SRC))))

CONTROLLER_SRC = $(wildcard $(SRC_DIR)/controller/*.cpp)
CONTROLLER_OBJ = $(addprefix $(OBJ_DIR)/controller/, $(notdir $(patsubst %.cpp, %.o, $(CONTROLLER_SRC))))

MODEL_SRC = $(wildcard $(SRC_DIR)/model/*.cpp)
MODEL_OBJ = $(addprefix $(OBJ_DIR)/model/, $(notdir $(patsubst %.cpp, %.o, $(MODEL_SRC))))

ZIP=zip -r
PACKED_FILES = src/* include/* res/* gui/* examples/* Makefile README.txt Doxyfile

all: app gui

app: $(APP_OBJ) $(CONTROLLER_OBJ) $(MODEL_OBJ)
	 $(CXX) $^ -o $(BIN_DIR)/$(BIN) $(LFLAGS)

gui:
	@cd $(GUI_DIR) && qmake -o ../$(GUI_QMAKE)/Makefile $(QFLAGS_DEBUG)
	$(MAKE) CXX=$(CXX) -C $(GUI_QMAKE)

# main.o
$(OBJ_DIR)/view/cli/%.o: $(SRC_DIR)/view/cli/%.cpp
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)/view/cli
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
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(GUI_QMAKE) $(DOXY_DIR) $(ZIP_FILE)

doxygen:
	@command -v doxygen >/dev/null 2>&1 \
		&& { doxygen $(DOXYFILE); true; } \
		|| echo "icp-make: Doxygen not installed."

pack:
	$(ZIP) $(ZIP_FILE) $(PACKED_FILES)

.PHONY: app gui doxygen pack clean run