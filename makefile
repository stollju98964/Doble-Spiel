# --------------------------
# Compiler & Flags
# --------------------------

CC     = gcc
CFLAGS = -g -Wall -I$(raylibfolder)/include
LDFLAGS = -lm -framework OpenGL -framework CoreFoundation -framework CoreGraphics -framework IOKit -framework Cocoa -framework CoreVideo

# --------------------------
# OS-spezifische Variablen
# --------------------------
ifeq ($(OS),Windows_NT)
	include makefile_windows.variables
else
	UNAME = $(shell uname)
	ifeq ($(UNAME),Linux)
		include makefile_linux.variables
	else
		include makefile_mac.variables
	endif
endif

raylibfolder = ./raylib
unityfolder  = ./unity

# --------------------------
# Selbst implementiertes Programm
# --------------------------

program_obj_files = stack.o bintree.o numbers.o timer.o highscore.o

doble: main.o $(program_obj_files)
	$(CC) $^ -o $@ $(LDFLAGS)

# Generische Regel für alle .o Files
%.o: %.c
	$(CC) -c $(FLAGS) -c $< -o $@

# --------------------------
# Initiales Programm (fertiges .a)
# --------------------------
doble_initial:
	$(CC) -o doble_initial $(BINARIES)/libdoble_complete.a

# --------------------------
# Unit Tests
# --------------------------

unitTests: test_numbers.o unity.o numbers.o bintree.o stack.o
	$(CC) $^ -o $@ $(LDFLAGS)


unity.o: $(unityfolder)/unity.c
	$(CC) -c $(FLAGS) $(unityfolder)/unity.c -o unity.o

test_numbers.o: test_numbers.c numbers.h
	$(CC) -c $(FLAGS) test_numbers.c -o test_numbers.o

# --------------------------
# Clean
# --------------------------
clean:
ifeq ($(OS),Windows_NT)
	del /f *.o doble doble_initial unitTests
else
	rm -f *.o doble doble_initial unitTests
endif
