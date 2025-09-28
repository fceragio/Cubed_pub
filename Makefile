NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP

RM = rm -f

SRC_DIR = src
OBJ_DIR = obj

BONUS_SRC_DIR = bonus_src
BONUS_OBJ_DIR = bonus_obj

INCLUDE = -Iinclude
BONUS_INCLUDE = -Ibonus_include

COLOR_GREEN = \033[0;32m
COLOR_END = \033[0m

# SOURCES normali (non bonus)
SRCS = $(wildcard $(SRC_DIR)/*.c) \
       $(wildcard $(SRC_DIR)/parsing/*.c) \
       $(wildcard $(SRC_DIR)/rendering/*/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# SOURCES bonus (ricorsivo tramite find)
BONUS_SRCS := $(shell find $(BONUS_SRC_DIR) -name '*.c')
BONUS_OBJS = $(patsubst $(BONUS_SRC_DIR)/%.c, $(BONUS_OBJ_DIR)/%.o, $(BONUS_SRCS))
BONUS_DEPS = $(BONUS_OBJS:.o=.d)

# ======== Target Principale ========
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $@
	@echo "$(COLOR_GREEN)$@ created.✅$(COLOR_END)"

# ======== Target Bonus ========
$(NAME)_bonus: $(BONUS_OBJS)
	$(CC) $(BONUS_OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $@
	@echo "$(COLOR_GREEN)$@ created.✅$(COLOR_END)"

bonus: $(NAME)_bonus

# ======== Compilazione Oggetti Normali ========
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -I/usr/include -Imlx_linux -c $< -o $@

# ======== Compilazione Oggetti Bonus ========
$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(BONUS_INCLUDE) -I/usr/include -Imlx_linux -c $< -o $@

# ======== Include file di dipendenze ========
-include $(DEPS)
-include $(BONUS_DEPS)

# ======== Pulizia ========
clean:
	$(RM) $(OBJS) $(DEPS)

clean_bonus:
	$(RM) $(BONUS_OBJS) $(BONUS_DEPS)

fclean: clean
	$(RM) $(NAME)
	@echo "$(COLOR_GREEN)$(NAME) cleaned.✅$(COLOR_END)"

fclean_bonus: clean_bonus
	$(RM) $(NAME)_bonus
	@echo "$(COLOR_GREEN)$(NAME)_bonus cleaned.✅$(COLOR_END)"

re: fclean all

.PHONY: all bonus clean clean_bonus fclean fclean_bonus re
