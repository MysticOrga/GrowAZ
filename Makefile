NAME := leaf_clicker
SRC := src/main.cpp src/Game.cpp src/Tree.cpp src/FloatingText.cpp

# Clang++ is preferred on macOS to avoid SDK compatibility issues with GCC.
CXX ?= clang++
CXXFLAGS := -std=c++17 -Wall -Wextra

# Adjust RAYLIB_ROOT if needed (brew default below).
RAYLIB_ROOT ?= /opt/homebrew/opt/raylib
INC := -I$(RAYLIB_ROOT)/include
LIB := -L$(RAYLIB_ROOT)/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL

all: $(NAME)

$(NAME): $(SRC)
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@ $(LIB)

.PHONY: clean fclean re run

clean:
	@echo "Nothing to clean (no intermediates)."

fclean:
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)
