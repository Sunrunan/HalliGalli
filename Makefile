
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/main

SRC= main.c ControlFunction.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:  main.c ControlFunction.h GameData.h
ControlFunction.o:  ControlFunction.c ControlFunction.h GameData.h

