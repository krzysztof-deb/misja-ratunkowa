CC=gcc
CFLAGS= -Wall -Wextra -g
LIBS=-lm
OBJ=main.o map.o pso.o logger.o utils.o 
pso:$(OBJ)
	$(CC) $(CFLAGS) -o pso $(OBJ) $(LIBS)
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean :
	rm -f $(OBJ) pso