CC = g++
RM = /bin/rm -rf

CFLAGS = -O3 -Wall -g

INCDIRS = -I. 
LIBDIRS = -L.
LIBS = -lGL -lGLEW -lglut -lm

BIN = sample
SRCS = main.cpp

OBJS = main.o 


# compile all '.o' files from their like named '.cpp' files and then link
#   them into a file name ${BIN}
${BIN} : ${OBJS}
	${CC} ${OBJS} ${LIBDIRS} ${LIBS} -o $@ 
.cpp.o :
	${CC} ${CFLAGS} ${INCDIRS} -c $< 

# specify clobber and clean as phony so they still run even if files
#   exist with the same names
.PHONY : clean remake
clean :
	${RM} ${BIN}
	${RM} ${OBJS}

remake : clean ${BIN}

#make a list of dependencies using makedepend
depend:
	makedepend -- $(CFLAGS) -- -Y $(SRCS)
