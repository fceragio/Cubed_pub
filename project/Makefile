NAME = cubed

CC = cc
CFLAGS = -Wall -Wextra -O3 -MMD -MP -Werror

RM = rm -f

SRCS = main.c \
		print_utils.c \
		parsing.c \
		parsing_assign_line_utils1.c \
		parsing_assign_line_utils2.c \
		parsing_blueprint_charmap.c \
		parsing_blueprint_charmap_utils.c \
		parsing_blueprint_prepare_fields.c \
		parsing_blueprint_prepare_fields_utils.c \
		parsing_blueprint_utils.c \
		parsing_blueprint_ok.c \
		parsing_check_file.c \
		parsing_check_line_utils1.c \
		parsing_check_line_utils2.c \
		parsing_create_blueprint_gnl1.c \
		parsing_create_blueprint_gnl2.c \
		parsing_create_blueprint_utils.c \
		parsing_map.c \
		parsing_map_utils.c \
		parsing_list_utils.c \
		rend_events.c \
		rend_math.c \
		rend_inits.c \
		rend_init_vs.c \
		rend_movement.c \
		rend_movement_turning.c \
		rend_wall_utils.c \
		rend_wall_utils_vrt_hit.c \
		rend_wall_utils_hrz_hit.c \
		render_utils.c \
		render_3d.c \
		render_3d_walls.c \
		render_3d_walls_utils.c \
		rend_debug.c \
		rend_debug_utils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

COLOR_GREEN=\033[0;32m
COLOR_END=\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L../mlx_linux -lmlx_Linux -L/usr/lib -I../mlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) created.✅$(COLOR_END)"

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) cleaned.✅$(COLOR_END)"

re: fclean all

.PHONY: all clean fclean re