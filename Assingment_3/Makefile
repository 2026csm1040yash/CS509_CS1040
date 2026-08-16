CC = gcc
CFLAGS = -Wall -Wextra -O2 -IInclude

TARGET = assignment3
SOURCES = Driver/main.c Src/mst.c Src/csr.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
