#Makefile#

NAME = cubed

CC = cc

CFLAGS = -Wall -Wextra #-Werror

RM = rm -f

SRCS = main.c \
		inits.c \
		map.c \
		events.c \
		math_utils.c \
		render_utils.c \
		render_2d.c \
		render_3d.c

OBJS = $(SRCS:.c=.o)

COLOR_GREEN=\033[0;32m
COLOR_END=\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L../mlx_linux -lmlx_Linux -L/usr/lib -I../mlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) created.✅$(COLOR_END)"

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS)
	@echo "$(COLOR_GREEN)$(NAME) cleaned.✅$(COLOR_END)"

re: fclean all

.PHONY: all clean fclean re