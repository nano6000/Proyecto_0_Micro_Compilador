CC = gcc
#LIBS = -lallegro
OBJS = Parser.c 
#Scanner.c Semantic_routines.c
OUT = compiler

compile: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) #`pkg-config --cflags --libs gtk+-3.0` 


debug: $(OBJS)
	$(CC) -g -o $(OUT) $(OBJS) #`pkg-config --cflags --libs gtk+-3.0`
	gdb $(OUT)

run:
	./$(OUT)

clean:
	rm $(OUT)

.PHONY: run debug compile

all: compile run