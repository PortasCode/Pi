CC = gcc 
CFLAGS = -std=c23 -pedantic -Wall -Wextra -Werror=pedantic

TARGET = wskazniki_program

all: $(TARGET)

$(TARGET): main.o tabela_akcje.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o tabela_akcje.o
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c 
tabela_akcje.o: tabela_akcje.c
	$(CC) $(CFLAGS) -c tabela_akcje.c

clean:
	rm -f $(TARGET) *.o
