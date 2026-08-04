# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 14:33:20 by gabrgarc          #+#    #+#              #
#    Updated: 2026/08/04 16:05:00 by mmaquine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./libft -I./minilibx-linux
BONUS_INCLUDES = -I./include_bonus -I./includes -I./libft -I./minilibx-linux

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

DIR_LIBX = minilibx-linux/
LIBX = $(DIR_LIBX)libmlx_Linux.a
LIBS = -L$(DIR_LIBX) -lmlx_Linux -lXext -lX11 -L$(DIR_LIBFT) -lft -lm -lz

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

BONUS_SRCS = \
	srcs_bonus/main.c \
	$(addprefix srcs_bonus/, $(ALGELIN_SRC)) \
	srcs_bonus/fileparser/cone_parser.c \
	srcs_bonus/fileparser/error_message.c \
	srcs_bonus/fileparser/openfile.c \
	srcs_bonus/fileparser/scene_obj_parser.c \
	srcs_bonus/fileparser/scene_obj_util.c \
	srcs_bonus/fileparser/unique_obj_parser.c \
	$(addprefix srcs_bonus/, $(RAYTRACING_SRCS)) \
	srcs_bonus/raytracing/cone_intersec.c \
	srcs_bonus/calc/pre_calc.c \
	$(addprefix srcs_bonus/, $(UTILS_SRCS)) \
	$(addprefix srcs_bonus/, $(WINDOW_SRC))
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
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BONUS_OBJS): | $(BONUS_OBJS_DIR)
$(BONUS_OBJS): Makefile

$(BONUS_OBJS_DIR):
	mkdir -p $(BONUS_OBJS_DIRS)

$(BONUS_OBJS_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DBONUS $(BONUS_INCLUDES) -c $< -o $@

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
