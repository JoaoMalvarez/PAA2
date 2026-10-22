CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = huffman
SRC = Codigo.c

# Alvo padrão: apenas compila o programa
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Alvo para rodar todo o fluxo de uma vez (compila, compacta e descompacta)
run: $(TARGET)
	./$(TARGET) -c texto.txt texto.huff
	./$(TARGET) -d texto.huff texto_recuperado.txt
	@echo "Fluxo completo executado com sucesso!"

# Alvo para limpar os arquivos gerados (binário e arquivos de teste)
clean:
	rm -f huffman huffman.exe texto.huff texto_recuperado.txt