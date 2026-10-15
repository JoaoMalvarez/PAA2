# Makefile do compactador Huffman

CC     = gcc
CFLAGS = -Wall -Wextra -g
TARGET = huffman
SRC    = Codigo.c
ARQ   ?= texto.txt

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

# make run              -> roda com texto.txt
# make run ARQ=outro.txt -> roda com outro arquivo
run: $(TARGET)
	./$(TARGET) $(ARQ)

clean:
	rm -f $(TARGET)

.PHONY: all run clean