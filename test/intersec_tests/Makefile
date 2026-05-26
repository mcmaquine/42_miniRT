CC      = cc
INCLUDES = -I../../includes -I../../libft -I../../minilibx-linux
CFLAGS  = -Wall -Wextra -Werror $(INCLUDES) -lm

LIBFT   = ../../libft/libft.a

SRCS    = test_intersec.c \
          ../../srcs/algelin/cofator.c \
          ../../srcs/algelin/matrix_det.c \
          ../../srcs/algelin/matrix_ops.c \
          ../../srcs/algelin/matrix_utils.c \
          ../../srcs/algelin/vector_measure.c \
          ../../srcs/algelin/vector_utils.c \
          ../../srcs/algelin/vectorvector.c \
          ../../srcs/fileparser/openfile.c \
          ../../srcs/fileparser/scene_obj_parser.c \
          ../../srcs/fileparser/scene_obj_util.c \
          ../../srcs/fileparser/unique_obj_parser.c \
          ../../srcs/raytracing/cyl_intersec.c \
          ../../srcs/raytracing/plane_intersec.c \
          ../../srcs/raytracing/sphere_intersec.c \
          ../../srcs/raytracing/tracer.c \
          ../../srcs/raytracing/tracer_utils.c \
          ../../srcs/utils/math_utils.c

NAME    = test_intersec

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(INLCUDE) -o $(NAME) -lm

clean:
	rm -f $(NAME)

re: clean all