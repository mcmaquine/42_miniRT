CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I../includes -I../libft -I../minilibx-linux/

LIBFT   = ../libft/libft.a

SRCS    = test_parser.c \
          print_scene.c \
          ../srcs/fileparser/openfile.c \
          ../srcs/fileparser/scene_obj_parser.c \
          ../srcs/fileparser/scene_obj_util.c \
          ../srcs/fileparser/unique_obj_parser.c

NAME    = test_parser

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all
