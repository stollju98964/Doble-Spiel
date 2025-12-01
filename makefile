CC = gcc
FLAGS = -g -Wall -lm

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
unityfolder = ./unity

# --------------------------
# Initiales Programm bauen (zum ausprobieren)
# --------------------------
doble_initial:
	$(CC) -o doble_initial $(BINARIES)/libdoble_complete.a

# --------------------------
# Selbst implementiertes Programm bauen
# --------------------------
program_obj_files = stack.o bintree.o numbers.o timer.o highscore.o

doble : main.o $(program_obj_files)
	$(CC) $(FLAGS) $^ -o doble

$(program_obj_filesobj_files): %.o: %.c
	$(CC) -c $(FLAGS) $^ -o $@

# --------------------------
# Unit Tests
# --------------------------
unitTests:
	echo "needs to be implemented"

# --------------------------
# Clean
# --------------------------
clean:
ifeq ($(OS),Windows_NT)
	del /f *.o doble
else
	rm -f *.o doble
endif