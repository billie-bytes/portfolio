# --- Configuration ---
CC = clang

# Compiler Flags:
# --target=wasm32: Target WebAssembly
# -nostdlib: No std libraries
# -Wl,--no-entry: No main() function required
# -Wl,--export=...: Explicitly export the functions JavaScript needs
# -Wl,--allow-undefined: Allow symbols to be unresolved
CFLAGS = --target=wasm32 -O3 -nostdlib \
     -Wl,--no-entry \
     -Wl,--export=get_g_input_buffer \
     -Wl,--export=get_g_output_buffer \
     -Wl,--export=get_frame \
     -Wl,--export=set_window_width \
     -Wl,--export=set_window_height \
     -Wl,--export=set_terminal \
     -Wl,--export=set_system_memory \
     -Wl,--export=set_system_cores \
     -Wl,--export=set_system_ram \
     -Wl,--export=set_memory_usage \
     -Wl,--export=set_system_battery \
     -Wl,--export=set_locale \
     -Wl,--export=set_uptime \
     -Wl,--export=init_system \
     -Wl,--export=exec_cmd \
     -Wl,--export=get_hexdump_ptr \
     -Wl,--allow-undefined \
     -Wall -Wextra \
     -Wl,--initial-memory=131072 \
     -I src

# --- Paths ---
SOURCE_DIR = src
OUTPUT_DIR = public
TARGET = $(OUTPUT_DIR)/kernel.wasm

# List all your C source files here
# Added shell.c so the command logic is included in the build
SRC = $(SOURCE_DIR)/kernel.c \
      $(SOURCE_DIR)/filesystem.c \
      $(SOURCE_DIR)/neofetch.c \
      $(SOURCE_DIR)/session.c \
      $(SOURCE_DIR)/utils.c \
      $(SOURCE_DIR)/shell.c

# --- Rules ---

all: $(TARGET)

# Compile C Source -> Public Wasm Binary
$(TARGET): $(SRC)
	@echo "Creating output directory..."
	mkdir -p $(OUTPUT_DIR)
	@echo "Compiling Kernel with all modules..."
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