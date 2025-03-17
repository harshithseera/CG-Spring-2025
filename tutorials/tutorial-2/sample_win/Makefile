# Define the compiler and the flags
CC = g++
RM = /bin/rm -rf
CFLAGS = -O3 -Wall -g -std=c++11

IMGUI_DIR = ./include/imgui
export PATH := ./include/glew/lib;$(PATH)

INCDIRS = -I. -I./include -I./include/glew/include -I./include/glfw/include -I${IMGUI_DIR} 
LIBDIRS = -L. -L./include/glew/lib -L./include/glfw/lib
LIBS = -lglew32 -lglfw3 -lopengl32 -lgdi32 -Wl,-rpath,include/glew/lib

# Define the target
BIN = sample.exe

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
clean:
	$(RM) "sample.exe"
	$(RM) "main.o"
	$(RM) "include\imgui\imgui.o"
	$(RM) "include\imgui\imgui_draw.o"
	$(RM) "include\imgui\imgui_widgets.o"
	$(RM) "include\imgui\imgui_tables.o"
	$(RM) "include\imgui\backends\imgui_impl_glfw.o"
	$(RM) "include\imgui\backends\imgui_impl_opengl3.o"

remake : clean ${BIN}

# Generate the dependencies
depend:
	makedepend -- $(CFLAGS) -- -Y $(SRCS)
