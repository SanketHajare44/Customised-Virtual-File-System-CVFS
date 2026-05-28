CC = gcc
CFLAGS = -Wall

SRC = src
INC = include

TARGET = cvfs

all:
	$(CC) $(CFLAGS) -I$(INC) $(SRC)/main.c $(SRC)/cvfs.c -o $(TARGET)

clean:
	rm -f $(TARGET)