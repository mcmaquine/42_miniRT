NAME = test_algelin

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I../../includes -I../../libft -I../../minilibx-linux/
LIBS = -Llibft -Lft -Lmlx -lm

LIBFT   = ../../libft/libft.a

SRCS 	=	../../srcs/algelin/cofator.c\
			../../srcs/algelin/matrix_det.c\
			../../srcs/algelin/matrix_ops.c\
			../../srcs/algelin/matrix_utils.c\
			../../srcs/algelin/vector_measure.c\
			../../srcs/algelin/vector_utils.c\
			../../srcs/algelin/vectorvector.c\
			./algelin_test.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $@ $(LIBS)

clean:
	rm -f $(NAME)

re: clean all