LDFLAG =
LIBS = 
EXECUTABLE_NAME = comm_manager

all:$(EXECUTABLE_NAME)

# Include Common Makefile
-include ${MAKE_UTILS_DIR}/Makefile.include

# Include Common Makefile
-include ${MAKE_UTILS_DIR}/Makefile.defs

# Generate binary file
CFLAG = -o

$(EXECUTABLE_NAME):$(C_OBJECTS)
	$(CC) $(C_OBJECTS) $(CFLAG) $(BIN_DIR)/$(EXECUTABLE_NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf *.o	
