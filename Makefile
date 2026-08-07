# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 14:33:20 by gabrgarc          #+#    #+#              #
#    Updated: 2026/08/07 01:29:42 by mmaquine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = miniRT
NAME_BONUS  = miniRT_bonus

CC     = cc
CFLAGS = -Wall -Wextra -Werror

DIR_LIBFT = ./libft
LIBFT     = $(DIR_LIBFT)/libft.a

DIR_LIBX = minilibx-linux/
LIBX     = $(DIR_LIBX)libmlx_Linux.a
LIBS     = -L$(DIR_LIBX) -lmlx_Linux -lXext -L$(DIR_LIBFT) -lX11 -lft -lm -lz

# ----------------------------------------------------------------------------
# Mandatory
# ----------------------------------------------------------------------------

INCLUDES = -I./includes -I./libft -I./minilibx-linux

MAIN_SRC = main.c

ALGELIN_SRC = \
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

OBJS_DIR  = objs/
OBJS      = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_DIRS = $(sort $(dir $(OBJS)))

# ----------------------------------------------------------------------------
# Bonus
# ----------------------------------------------------------------------------

INCLUDES_BONUS = -I./include_bonus -I./libft -I./minilibx-linux
LIBS_BONUS = $(LIBS) -lpthread

MAIN_SRC_BONUS = main_bonus.c

ALGELIN_SRC_BONUS = \
	algelin/vector_measure.c \
	algelin/vector_utils.c \
	algelin/vectorvector.c

PARSER_SRCS_BONUS = \
	fileparser/openfile.c \
	fileparser/openfile_util.c \
	fileparser/cone_parser.c \
	fileparser/scene_obj_parser.c \
	fileparser/scene_obj_util.c \
	fileparser/unique_obj_parser.c \
	fileparser/material_parser_bonus.c \
	fileparser/error_message.c

RAYTRACING_SRCS_BONUS = \
	raytracing/cyl_intersec.c \
	raytracing/normals.c \
	raytracing/phong.c \
	raytracing/plane_intersec.c \
	raytracing/sphere_intersec.c \
	raytracing/tracer.c \
	raytracing/cone_intersec.c \
	raytracing/reflection_bonus.c \
	raytracing/texture_bonus.c \
	raytracing/tracer_utils.c

BVH_SRCS_BONUS = \
	bvh/build_bvh.c \
	bvh/compare_axis.c \
	bvh/get_aabb.c \
	bvh/get_boxes.c \
	bvh/group_box.c \
	bvh/hit_box.c \
	bvh/hit_bvh.c \
	bvh/init_bvh.c \
	bvh/intersect_bvh.c

CALC_SRCS_BONUS = \
	calc/calc_normals.c

THREAD_SRCS_BONUS = \
	threads/thread.c \
	threads/thread_routine.c

UTILS_SRCS_BONUS = \
	utils/math_utils.c \
	utils/free.c \
	utils/num_threads.c \
	utils/get_current_time.c \
	utils/real_min.c \
	utils/real_max.c \
	utils/array_objs.c \
	utils/count_objs.c

WINDOW_SRC_BONUS = \
	window/start_window.c \
	window/events.c

SRCS_BONUS := $(MAIN_SRC_BONUS) $(ALGELIN_SRC_BONUS) $(PARSER_SRCS_BONUS) \
	$(RAYTRACING_SRCS_BONUS) $(UTILS_SRCS_BONUS) $(WINDOW_SRC_BONUS) \
	$(CALC_SRCS_BONUS) $(THREAD_SRCS_BONUS) $(BVH_SRCS_BONUS)

SRCS_BONUS := $(addprefix srcs_bonus/, $(SRCS_BONUS))

OBJS_DIR_BONUS = objs_bonus/
OBJS_BONUS      = $(addprefix $(OBJS_DIR_BONUS), $(SRCS_BONUS:.c=.o))
OBJS_DIRS_BONUS = $(sort $(dir $(OBJS_BONUS)))

# ----------------------------------------------------------------------------
# Rules
# ----------------------------------------------------------------------------

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIBS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(LIBX)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $@ $(LIBS_BONUS)

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIRS)

$(OBJS_DIR)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_BONUS): | $(OBJS_DIR_BONUS)

$(OBJS_DIR_BONUS):
	mkdir -p $(OBJS_DIRS_BONUS)

$(OBJS_DIR_BONUS)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

$(LIBFT): $(DIR_LIBFT)
	$(MAKE) -C $< all

$(LIBX): $(DIR_LIBX)
	$(MAKE) -C $< all

val:
	@valgrind -q --leak-check=full --track-origins=yes \
	--track-fds=yes --show-leak-kinds=all ./$(NAME)

val_bonus:
	@valgrind -q --leak-check=full --track-origins=yes \
	--track-fds=yes --show-leak-kinds=all ./$(NAME_BONUS)

debug: CFLAGS += -g
debug: re

debug_bonus: CFLAGS += -g
debug_bonus: re_bonus

clean:
	rm -rf $(OBJS_DIR) $(OBJS_DIR_BONUS)
	$(MAKE) -C $(DIR_LIBFT) clean

fclean: clean
	$(MAKE) -C $(DIR_LIBFT) fclean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus val val_bonus debug debug_bonus
