# Pre-compiler and Compiler flags
#CXX_FLAGS := -Wall -Wextra -Werror -pedantic -std=c++2a  -ggdb
CXX_FLAGS := -Wall -Wextra -Werror -pedantic -std=c++2a 
PRE_FLAGS := -MMD -MP
CXX :=clang++
# Project directory structure
BIN := bin
SRC := src
#LIB := lib
LIB :=
INC := include /opt/local/include
MAINFILE := $(SRC)/driver.cc

# Build directories and output
TARGET := $(BIN)/exec
TARGET1 := $(BIN)/test
BUILD := build
BUILD1 := build1
RUNTEST := test

# Library search directories and flags
EXT_LIB :=
LDFLAGS :=
LDPATHS := $(addprefix -L,$(LIB) $(EXT_LIB))

# Include directories
INC_DIRS := $(INC) $(shell find $(SRC) -type d) 
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Construct build output and dependency filenames
SRCS := $(shell find $(SRC) -name *.cc)
OBJS := $(subst $(SRC)/,$(BUILD)/,$(addsuffix .o,$(basename $(SRCS))))
OBJS1 := $(subst $(SRC)/,$(BUILD1)/,$(addsuffix .o,$(basename $(SRCS))))
DEPS := $(OBJS:.o=.d)

# Run task
run: build
	@echo "🚀 Executing..."
	./$(TARGET) $(ARGS)
test:$(TARGET1)
	@echo "🚀 Build test case..."
	./$(TARGET1) $(ARGS)

# Build task
build: clean all

# Main task
all: $(TARGET)


# Task producing target from built files
$(TARGET): $(OBJS)
	@echo "🚧 Building..."
	mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDPATHS) $(LDFLAG) -L/opt/local/lib/ -lCatch2 -lCatch2Main
# Task producing target from built files
$(TARGET1): $(OBJS1)
	@echo "🚧 Building..."
	mkdir -p $(dir $@)
	$(CXX) $(OBJS1) -o $@ $(LDPATHS) $(LDFLAG) -L/opt/local/lib/ -lCatch2 -lCatch2Main

# Compile all cpp files
# $(CXX) $(CXX_FLAGS) $(PRE_FLAGS) $(INC_FLAGS) -c -o $@ $< $(LDPATHS) $(LDFLAGS)
$(BUILD)/%.o: $(SRC)/%.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(PRE_FLAGS) $(INC_FLAGS) -c -o $@ $<  $(LDFLAGS)

$(BUILD1)/%.o: $(SRC)/%.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) $(PRE_FLAGS) $(INC_FLAGS) -D RUNTEST -c -o $@ $<  $(LDFLAGS)

# Clean task
.PHONY: clean
clean:
	@echo "🧹 Clearing..."
	rm -rf build

# Include all dependencies
-include $(DEPS)
