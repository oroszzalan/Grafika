CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
LDFLAGS = -lfreeglut -lopengl32 -lglu32 -pthread

TARGET = program.exe

all: $(TARGET)

$(TARGET): main.o
	$(CC) -o $(TARGET) main.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)
