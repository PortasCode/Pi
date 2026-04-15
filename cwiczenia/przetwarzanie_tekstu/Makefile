CC = gcc
CFLAGS = -std=c23 -pedantic -Wall -Wextra

TARGET = program

all: $(TARGET)

$(TARGET): main.o manipulator.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o manipulator.o

main.o: main.c manipulator.h
	$(CC) $(CFLAGS) -c main.c

manipulator.o: manipulator.c manipulator.h
	$(CC) $(CFLAGS) -c manipulator.c

clean:
	rm -f *.o $(TARGET)
