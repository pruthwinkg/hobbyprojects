LDFLAG = -shared
LIBS = 
EXECUTABLE_NAME =
LIBRARY_NAME = libcomm_mgr.so

all: $(LIBRARY_NAME)

#ifeq ($(CC), gcc -DTEST_COMM_MGR_LIB)
SUBDIRS = \
	test_comm_mgr_lib \

#endif

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
