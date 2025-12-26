# --- Configuration ---
CC = clang
CFLAGS = --target=wasm32 -O3 -nostdlib -Wl,--no-entry -Wl,--export-all -Wall -Wextra -Wl,--initial-memory=131072

# --- Paths ---
SOURCE_DIR = src
OUTPUT_DIR = public
TARGET = $(OUTPUT_DIR)/kernel.wasm
SRC = $(SOURCE_DIR)/kernel.c

# --- Rules ---

all: $(TARGET)

# Compile C Source -> Public Wasm Binary
$(TARGET): $(SRC)
	@echo "Creating output directory..."
	mkdir -p $(OUTPUT_DIR)
	@echo "Compiling Kernel..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
	@echo "Build successful! Binary placed in $(OUTPUT_DIR)/"

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)

# Serve specifically from the 'public' folder
serve:
	@echo "Starting server at http://localhost:8000"
	@echo "Serving content from ./public"
	python3 -m http.server --directory $(OUTPUT_DIR)

.PHONY: all clean serve