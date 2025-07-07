NAME = cubed

CC = cc
CFLAGS = -Wall -Wextra -O3 -MMD -MP #-Werror

RM = rm -f

SRCS = main.c \
		inits.c \
		map.c \
		events.c \
		movement.c \
		math_utils.c \
		render_utils.c \
		render_2d.c \
		render_3d.c \
		print_utils.c \
		parsing.c \
		parsing_assign_line_utils1.c \
		parsing_assign_line_utils2.c \
		parsing_blueprint_charmap.c \
		parsing_blueprint_charmap_utils.c \
		parsing_blueprint_utils.c \
		parsing_check_file.c \
		parsing_check_line_utils1.c \
		parsing_check_line_utils2.c \
		parsing_create_blueprint_gnl1.c \
		parsing_create_blueprint_gnl2.c \
		parsing_create_blueprint_utils.c \
		parsing_list_utils.c

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