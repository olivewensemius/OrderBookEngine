CC = g++
CFLAGS = -I include -O3 -Wall
SRC = src/main.cpp src/OrderBook.cpp
OUT = build/OrderBook

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

run: $(OUT)
	./$(OUT)

clean:
	rm -rf build/*
