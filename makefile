CC=gcc
LDFLAG=
CFLAG=-Wall
EXEC=res
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all:$(EXEC)

$(EXEC):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAG)

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAG)

.PHONY:clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
	rm -rf compile_commands.json
	rm -rfd html/
	rm -rfd latex/

clangd: clean
	bear make

run: $(EXEC)
	./$(EXEC)

doxy:
	doxygen Doxyfile
