# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 14:33:20 by gabrgarc          #+#    #+#              #
#    Updated: 2026/08/08 17:23:22 by gabrgarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = miniRT
NAME_BONUS  = miniRT_bonus

CC     = cc
CFLAGS = -Wall -Wextra -Werror -O3

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
	fileparser/openfile_util.c \
	fileparser/scene_obj_parser.c \
	fileparser/scene_obj_util.c \
	fileparser/scene_fill_utils.c \
	fileparser/unique_obj_parser.c \
	fileparser/unique_obj_parser_utils.c \
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
	algelin/vector_measure_bonus.c \
	algelin/vector_utils_bonus.c \
	algelin/vectorvector_bonus.c

PARSER_SRCS_BONUS = \
	fileparser/openfile_bonus.c \
	fileparser/cone_parser_bonus.c \
	fileparser/scene_obj_parser_bonus.c \
	fileparser/scene_obj_util_bonus.c \
	fileparser/unique_obj_parser_bonus.c \
	fileparser/material_parser_bonus.c \
	fileparser/error_message_bonus.c

RAYTRACING_SRCS_BONUS = \
	raytracing/cyl_intersec_bonus.c \
	raytracing/normals_bonus.c \
	raytracing/phong_bonus.c \
	raytracing/plane_intersec_bonus.c \
	raytracing/sphere_intersec_bonus.c \
	raytracing/tracer_bonus.c \
	raytracing/cone_intersec_bonus.c \
	raytracing/reflection_bonus.c \
	raytracing/texture_bonus.c \
	raytracing/tracer_utils_bonus.c

BVH_SRCS_BONUS = \
	bvh/build_bvh_bonus.c \
	bvh/compare_axis_bonus.c \
	bvh/get_aabb_bonus.c \
	bvh/get_boxes_bonus.c \
	bvh/group_box_bonus.c \
	bvh/hit_box_bonus.c \
	bvh/hit_bvh_bonus.c \
	bvh/init_bvh_bonus.c \
	bvh/intersect_bvh_bonus.c

CALC_SRCS_BONUS = \
	calc/calc_normals_bonus.c

THREAD_SRCS_BONUS = \
	threads/thread_bonus.c \
	threads/thread_routine_bonus.c

UTILS_SRCS_BONUS = \
	utils/math_utils_bonus.c \
	utils/free_bonus.c \
	utils/num_threads_bonus.c \
	utils/get_current_time_bonus.c \
	utils/real_min_bonus.c \
	utils/real_max_bonus.c \
	utils/array_objs_bonus.c \
	utils/valid_extension_bonus.c \
	utils/count_objs_bonus.c

WINDOW_SRC_BONUS = \
	window/start_window_bonus.c \
	window/events_bonus.c

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
