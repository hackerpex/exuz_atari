CC = clang
CFLAGS = -Wall -Wextra -std=c11 -O2 -I/opt/homebrew/include/SDL2
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -framework CoreFoundation


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
