SRC =	$(shell find . -name "*.c") \
	$(shell find .. -name "*.c")
OBJ =	$(SRC:.c=.o)


CC =	gcc
FLAGS=	-Wall -Werror -Wextra -pedantic -g3

huffman: $(OBJ)
	$(CC) $^ $(FLAGS) -o huffman

%o: %.c
	@$(CC) -c -I. -Iheap $< $(FLAGS) -o $@ 


.PHONY: clean
clean:
	rm -f $(OBJ) huffman
