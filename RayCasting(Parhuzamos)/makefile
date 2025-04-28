CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
LDFLAGS = -lfreeglut -lopengl32 -lglu32 -pthread

TARGET = program.exe

all: $(TARGET)

$(TARGET): pthread.o
	$(CC) -o $(TARGET) pthread.o $(LDFLAGS)

pthread.o: pthread.c
	$(CC) $(CFLAGS) -c pthread.c

clean:
	rm -f *.o $(TARGET)
