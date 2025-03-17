# Get the OS type
UNAME := $(shell uname)

# Define the compiler and the flags
CC = g++
RM = /bin/rm -rf
CFLAGS = -O3 -Wall -g -std=c++11

IMGUI_DIR = ./include/imgui

# Linux specific flags
ifeq ($(UNAME), Linux)
	INCDIRS = -I. -I./include -I${IMGUI_DIR}
	LIBDIRS = -L.
	LIBS = -lGL -lGLEW -lm -lglfw
endif

# Mac OS X specific flags
ifeq ($(UNAME), Darwin)
	INCDIRS = -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/opt/homebrew/Cellar/glfw/3.4/include -I./include -I${IMGUI_DIR}
	LIBDIRS = -L. -L/usr/local/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib -L/opt/homebrew/Cellar/glfw/3.4/lib
	LIBS = -framework OpenGL -lGLEW -lglfw
endif

# Define the target
BIN = sample

# Define the source files
SRCS = main.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Define the rules
${BIN} : ${OBJS}
	${CC} ${OBJS} ${LIBDIRS} ${LIBS} -o $@ 
.cpp.o :
	${CC} ${CFLAGS} ${INCDIRS} -c $< -o $@

.PHONY : clean remake
# Clean up the directory
clean :
	${RM} ${BIN}
	${RM} ${OBJS}

remake : clean ${BIN}

# Generate the dependencies
depend:
	makedepend -- $(CFLAGS) -- -Y $(SRCS)
