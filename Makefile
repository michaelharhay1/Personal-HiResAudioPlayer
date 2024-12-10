# Set compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include -I/opt/homebrew/opt/sfml/include -stdlib=libc++ -ObjC++

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
EXEC_DIR = $(BUILD_DIR)
EXEC = $(EXEC_DIR)/audio_player

# Object files
OBJ_FILES = $(OBJ_DIR)/audio_player.o $(OBJ_DIR)/gui.o $(OBJ_DIR)/main.o $(OBJ_DIR)/file_browser.o

# Targets
all: $(EXEC)

# Compile .cpp files to .o files
$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(OBJ_DIR)  # Make sure the obj/ directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .mm files to .o files
$(OBJ_DIR)/%.o: src/%.mm
	@mkdir -p $(OBJ_DIR)  # Make sure the obj/ directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link the object files to create the executable
$(EXEC): $(OBJ_FILES)
	@mkdir -p $(EXEC_DIR)  # Make sure the build/ directory exists
	$(CXX) $(OBJ_FILES) -L/opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -framework Cocoa -framework Foundation -o $(EXEC)

# Clean up object files and executable
clean:
	rm -rf $(OBJ_DIR) $(EXEC_DIR)
