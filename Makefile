NAME = cubed

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

RM = rm -f

SRC_DIR = project/Cubed
OBJ_DIR = $(SRC_DIR)/obj

COLOR_GREEN = \033[0;32m
COLOR_END = \033[0m

SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/parsing/*.c) \
       $(wildcard $(SRC_DIR)/rendering/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) created.✅$(COLOR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) cleaned.✅$(COLOR_END)"

re: fclean all

.PHONY: all clean fclean re
