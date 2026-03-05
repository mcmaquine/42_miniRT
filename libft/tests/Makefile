NAME = test
INCLUDES = -I../
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)
LIBS = -Llibft

MAIN_SRC = tests.c

LIBFT = ../libft.a

OBJ = $(MAIN_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
