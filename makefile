# ===============================
# Compiler & Flags
# ===============================
CXX = g++
CXXFLAGS = -std=c++17 -I./include -Wall
LDFLAGS = -L./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -mconsole

# ===============================
# Source & Object Files
# ===============================
SRC := $(shell find src -name "*.cpp")
OBJ := $(patsubst src/%.cpp,build/%.o,$(SRC))
TOTAL := $(words $(SRC))

# ===============================
# Target executable
# ===============================
TARGET = main.exe

# ===============================
# Default target: build executable
# ===============================
all: $(TARGET)

# ===============================
# Link objects -> main.exe
# ===============================
$(TARGET): $(OBJ)
	@echo "Linking $(TARGET)..."
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# ===============================
# Compile .cpp -> .o with progress bar
# ===============================
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	# Tính thứ tự file hiện tại trong danh sách SRC
	@POS=$(shell echo "$(SRC)" | tr ' ' '\n' | grep -n "$<" | cut -d: -f1); \
	PERC=$$(awk "BEGIN{printf \"%d\", ($$POS*100)/$(TOTAL)}"); \
	NUMHASH=$$(($$PERC/2)); \
	BAR=$$(printf "%0.s#" $$(seq 1 $$NUMHASH)); \
	BAR=$$BAR$$(printf "%0.s " $$(seq 1 $$((50-$$NUMHASH)))); \
	echo -ne "Compiling $< [$${BAR}] $$PERC%%\r"; \
	$(CXX) $(CXXFLAGS) -c $< -o $@; \
	echo -ne "Compiling $< [$${BAR}] $$PERC%%\n"

# ===============================
# Run program with Windows terminal
# ===============================
run: $(TARGET)
	@echo "Running $(TARGET) in new Windows terminal..."
	cmd /k "$(TARGET)"

# ===============================
# Clean build
# ===============================
clean:
	@echo "Cleaning..."
	rm -rf build $(TARGET)

# ===============================
# Phony targets
# ===============================
.PHONY: all clean run
