# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 14:33:20 by gabrgarc          #+#    #+#              #
#    Updated: 2026/06/27 16:11:20 by gabrgarc         ###   ########.fr        #
#    Updated: 2026/05/15 15:07:36 by gabrgarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./libft -I./minilibx-linux

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

DIR_LIBX = minilibx-linux/
LIBX = $(DIR_LIBX)libmlx_Linux.a
LIBS = -L$(MLX_DIR) -lmlx_Linux -lXext -Llibft -lX11 -lft -Lmlx -lm -lz

MAIN_SRC = main.c

ALGELIN_SRC = \
	algelin/cofator.c \
	algelin/matrix_det.c \
	algelin/matrix_ops.c \
	algelin/matrix_utils.c \
	algelin/vector_measure.c \
	algelin/vector_utils.c \
	algelin/vectorvector.c

PARSER_SRCS = \
	fileparser/openfile.c \
	fileparser/scene_obj_parser.c \
	fileparser/scene_obj_util.c \
	fileparser/unique_obj_parser.c \
	fileparser/error_message.c

RAYTRACING_SRCS = \
	raytracing/cyl_intersec.c \
	raytracing/normals.c \
	raytracing/phong.c \
	raytracing/plane_intersec.c \
	raytracing/sphere_intersec.c \
	raytracing/tracer.c \
	raytracing/tracer_utils.c

CALC_SRCS = \
	calc/calc_normals.c

UTILS_SRCS = \
	utils/math_utils.c \
	utils/free.c

WINDOW_SRC = \
	window/start_window.c \
	window/events.c

SRCS := $(MAIN_SRC) $(ALGELIN_SRC) $(PARSER_SRCS) $(RAYTRACING_SRCS) \
	$(UTILS_SRCS) $(WINDOW_SRC) $(CALC_SRCS)
 
SRCS := $(addprefix srcs/, $(SRCS))

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_DIRS = $(sort $(dir $(OBJS)))

BONUS_SRCS := $(filter-out srcs/main.c srcs/raytracing/phong.c \
	srcs/fileparser/scene_obj_parser.c srcs/calc/calc_normals.c, $(SRCS))
BONUS_SRCS += srcs/main_bonus.c \
	srcs/raytracing/phong_bonus.c \
	srcs/raytracing/texture_bonus.c \
	srcs/raytracing/reflection_bonus.c \
	srcs/fileparser/scene_obj_parser_bonus.c \
	srcs/fileparser/material_parser_bonus.c \
	srcs/calc/calc_normals_bonus.c
BONUS_OBJS_DIR = objs_bonus/
BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR), $(BONUS_SRCS:.c=.o))
BONUS_OBJS_DIRS = $(sort $(dir $(BONUS_OBJS)))
MANDATORY_STAMP = .mandatory
BONUS_STAMP = .bonus

all: $(MANDATORY_STAMP)

$(MANDATORY_STAMP): $(OBJS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $(NAME) $(LIBS)
	rm -f $(BONUS_STAMP)
	touch $@

bonus: $(BONUS_STAMP)

$(BONUS_STAMP): $(BONUS_OBJS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $(NAME) $(LIBS)
	rm -f $(MANDATORY_STAMP)
	touch $@

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIRS)

$(OBJS_DIR)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_OBJS): | $(BONUS_OBJS_DIR)
$(BONUS_OBJS): Makefile

$(BONUS_OBJS_DIR):
	mkdir -p $(BONUS_OBJS_DIRS)

$(BONUS_OBJS_DIR)%.o: %.c
	$(CC) $(CFLAGS) -DBONUS $(INCLUDES) -c $< -o $@

$(LIBFT): $(DIR_LIBFT)
	$(MAKE) -C $< all

$(LIBX): $(DIR_LIBX)
	$(MAKE) -C $< all

val:
	@valgrind -q --leak-check=full --track-origins=yes \
	--track-fds=yes --show-leak-kinds=all ./$(NAME)

debug: CFLAGS += -g
debug: re

clean:
	rm -rf $(OBJS_DIR) $(BONUS_OBJS_DIR)
	rm -f $(MANDATORY_STAMP) $(BONUS_STAMP)
	$(MAKE) -C $(DIR_LIBFT) clean
	$(MAKE) -C $(DIR_LIBX) clean

fclean: clean
	$(MAKE) -C $(DIR_LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
