CC = gcc
EXEC = IsingModel
INCLUDES = -I../include/
CFLAGS += $(INCLUDES)
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all : $(EXEC)


%.o : %.c
	$(CC) -o $@ -c $<


$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o $(EXEC)
