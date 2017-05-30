CC=gcc

SOURCES = main.c util.c

INC = -I./include

OBJECTS = ${SOURCES:.c=.o}

target = out 


$(target) : $(OBJECTS)
	$(CC) -o $(target) $(OBJECTS) $(INC) 

clean:
	rm $(target) *.o
