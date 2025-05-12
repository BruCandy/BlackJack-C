TARGET = blackjack
SRCS = main.c screen.c assets.c deck.c hand.c dealer.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O2 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf


all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
