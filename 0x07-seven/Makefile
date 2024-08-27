# OBJS specifies which files to compile as part of the project
OBJS = main_2.cpp

# CC specifies which compiler to use
CC = g++

# COMPILER_FLAGS specifies the additional compilation options being used
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libs to be linked
LINKER_FLAGS = -lSDL2 -lSDL2_image

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main_2

# This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
