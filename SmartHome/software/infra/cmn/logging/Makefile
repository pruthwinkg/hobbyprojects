LDFLAG = -shared
LIBS = 
EXECUTABLE_NAME =
LIBRARY_NAME = liblogging.so

all: $(LIBRARY_NAME)

# Include Common Makefile
-include ${MAKE_UTILS_DIR}/Makefile.include

# Include Common Makefile
-include ${MAKE_UTILS_DIR}/Makefile.defs


# Generate shared library
CFLAG = -o
LIBFLAG = -fPIC

$(LIBRARY_NAME):$(C_OBJECTS)
	$(CC) $(C_OBJECTS) $(LDFLAG) $(CFLAG) $(LIB_DIR)/$(LIBRARY_NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFLAG) $(INCLUDE) -c $< -o $@


clean:
	rm -rf *.o	
