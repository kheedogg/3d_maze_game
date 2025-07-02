# Makefile for DoMazeGame

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -O2

# Libraries
LIBS = -lraylib -lsqlite3 -lm

# macOS specific flags
ifeq ($(shell uname), Darwin)
    LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    CFLAGS += -I/opt/homebrew/include
    LDFLAGS = -L/opt/homebrew/lib
endif

# Linux specific flags
ifeq ($(shell uname), Linux)
    LIBS += -lGL -lpthread -ldl -lrt -lX11
endif

# Source files
SOURCES = main.c

# Output executable
OUTPUT = domazegame

# Default target
all: $(OUTPUT)

# Compile the game
$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(OUTPUT) $(SOURCES) $(LIBS)

# Web build using Emscripten
web: $(SOURCES)
	emcc -o domazegame.html $(SOURCES) $(CFLAGS) -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY --shell-file shell.html -lraylib -lsqlite3
	@echo "Web build complete. Open domazegame.html in a web browser."

# Clean build files
clean:
	rm -f $(OUTPUT) domazegame.html domazegame.js domazegame.wasm

# Install dependencies (macOS with Homebrew)
install-deps-mac:
	brew install raylib sqlite3

# Install dependencies (Ubuntu/Debian)
install-deps-linux:
	sudo apt-get update
	sudo apt-get install libraylib-dev libsqlite3-dev

# Run the game
run: $(OUTPUT)
	./$(OUTPUT)

.PHONY: all web clean install-deps-mac install-deps-linux run