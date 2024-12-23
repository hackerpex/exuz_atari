CC = clang
#normal mode
# CFLAGS = -Wall -Wextra -std=c11 -O2  $(shell sdl2-config --cflags)
#debug mode
CFLAGS = -Wall -Wextra -std=c11 -O0  -g $(shell sdl2-config --cflags)

LDFLAGS = $(shell sdl2-config --libs) -framework CoreFoundation


SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = exuz_atari

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
