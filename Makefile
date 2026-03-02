# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 14:33:20 by gabrgarc          #+#    #+#              #
#    Updated: 2026/03/02 13:51:04 by mmaquine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./libft -I./minilibx-linux
LIBS = -Llibft -lft -lmlx -lm

MAIN_SRC = main.c

SRCS := $(MAIN_SRC)

SRCS := $(addprefix srcs/, $(SRCS))

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_DIRS = $(sort $(dir $(OBJS)))

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

DIR_LIBX = ./minilibx-linux
LIBX = $(DIR_LIBX)/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(RDFLAGS)

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIRS)

$(OBJS_DIR)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(DIR_LIBFT)
	$(MAKE) -C $< all

$(LIB): $(DIR_LIBX)
	$(MAKE) -C $< all

val:
	@valgrind -q --leak-check=full --track-origins=yes \
	--track-fds=yes --show-leak-kinds=all \
	--suppressions=readline.supp ./$(NAME)

debug: CFLAGS += -g
debug: re

clean:
	$(MAKE) -C $(DIR_LIBFT) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(DIR_LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
