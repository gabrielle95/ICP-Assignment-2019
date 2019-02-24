# Variables
PROJECT = chess
BIN = $(PROJECT)

CXX = $(shell command -v g++-7.3 >/dev/null 2>&1 && echo -n "g++-7.3" || echo -n "g++")
RM = rm -rf
ZIP = zip -r

CFLAGS = -Wall -Wextra -c --std=c++17
CFLAGS_RELEASE = -O2
CFLAGS_DEBUG = -O0 -g -DDEBUG
QFLAGS =
QFLAGS_DEBUG = CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug

#-lboost_system -lboost_filesystem
LFLAGS = -lpthread
LFLAGS += $(shell command -v g++-7.3 >/dev/null 2>&1 && echo -n "-static-libstdc++")

SRC_FOLDER = src
BIN_FOLDER = bin
OBJ_FOLDER = obj
GUI_FOLDER = gui
GUI_WORK_FOLDER = gui-work

ZIP_FILE = xpacak01.zip
PACKED_FILES = src/* include/* res/* gui/* example/* Makefile README.txt doxyconfig
DOXYFILE = doxyconfig
DOXY_DIR = doc

INCLUDES = -Iinclude

APP_SRCS = $(wildcard $(SRC_FOLDER)/app/*.cpp)
APP_OBJS = $(addprefix $(OBJ_FOLDER)/app/, $(notdir $(patsubst %.cpp, %.o, $(APP_SRCS))))

# Targets
release: CFLAGS += $(CFLAGS_RELEASE)
release: build

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: QFLAGS += $(QFLAGS_DEBUG)
debug: build

build: app gui

app: $(APP_OBJS)
	$(CXX) $^ -o $(BIN_FOLDER)/$(BIN) $(LFLAGS)

gui:
	@cd $(GUI_FOLDER) && qmake -o ../$(GUI_WORK_FOLDER)/Makefile $(QFLAGS)
	$(MAKE) CXX=$(CXX) -C $(GUI_WORK_FOLDER)

$(OBJ_FOLDER)/app/%.o: $(SRC_FOLDER)/app/%.cpp
	@mkdir -p $(BIN_FOLDER) $(OBJ_FOLDER)/app
	$(CXX) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	$(RM) $(BIN_FOLDER) $(OBJ_FOLDER) $(ZIP_FILE) $(DOXY_DIR) $(GUI_WORK_FOLDER)

pack:
	$(ZIP) $(ZIP_FILE) $(PACKED_FILES)

run: app gui
	@cd ./$(BIN_FOLDER) && ./$(BIN) &
	@cd ./$(BIN_FOLDER) && ./$(PROJECT)

doxygen:
	@command -v doxygen >/dev/null 2>&1 \
		&& { doxygen $(DOXYFILE); true; } \
		|| echo "icp-make: Doxygen not installed."

.PHONY: build release debug app gui run clean pack doxygen