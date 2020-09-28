# this makefile is completely broken
# program executable name
TARGET = sleep
TARGET2 = busy_wait_delay

# compiler flags
CFLAGS =  -g -Wall

# linker flags
LDFLAGS = -g -lpthread

# list of sources
SOURCES = sleep.c
SOURCES2 = busy_wait_delay.c

# default rule, to compile everything
all: $(TARGET)

# define object files
OBJECTS = sleep.o
OBJECTS2 = busy_wait_delay.o

# link programs
$(TARGET): $(OBJECTS)
	gcc $(LDFLAGS) -o $@ $^

# compile
%.o : %.c
	gcc $(CFLAGS) -c -o $(TARGET) $< && gcc $(CFLAGS) -c -o $(TARGET2)

# cleaning
clean:
	rm -f $(TARGET) $(OBJECTS) $(TARGET2) $(OBJECTS2)

# running
run:
	./$(TARGET)
